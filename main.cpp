#include "Parser.hpp"
#include <getopt.h>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <system_error> // for std::error_code

using namespace std;
namespace fs = std::filesystem;

struct CmdOptions{
    string inFilename = "";
    bool manual = false;
    string outputDir = "output"; // Default output directory
};

void printHelp(){
    cout << ".VTT file parsing app\n"
    << "Usage: ./parser [options]\n"
    << "Options:\n"
    << "  -h, --help                       Display this help message\n"
    << "  -m, --manual <.vtt_filename>     Registration file for bank accounts\n"
    << "  -a, --auto                       Automatically parse all files present in designated folder\n"
    << "  -o, --output <directory>         Specify output directory for parsed files (default: 'output')\n";
    exit(0);
}

// function to parse command line options 
void getMode(int argc, char * argv[], CmdOptions &cmdOptions) {
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int index = 0;  

    option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"manual", required_argument, nullptr, 'm'},
        {"auto", no_argument, nullptr, 'a'},
        {"output", required_argument, nullptr, 'o'},
        {nullptr, 0, nullptr, '\0'},
    };  // long_options[]

    bool fileFlag = false;
  
    while ((choice = getopt_long(argc, argv, "hm:ao:", long_options, &index)) != -1) {
        switch (choice) {
            case 'a': {
                cmdOptions.manual = false;
                cout << "mode a\n";
                break;
            }

            case 'm': {
                cmdOptions.manual = true;
                cmdOptions.inFilename = optarg; // Fixed: Use optarg instead of argv[2]
                fileFlag = true;
                cout << "mode m\n";
                break;
            }

            case 'h': {
                printHelp();
                exit(0);
                break;
            }
            
            case 'o': {
                cmdOptions.outputDir = optarg;
                cout << "Output directory set to: " << cmdOptions.outputDir << "\n";
                break;
            }

            default:
                cerr << "Registration file failed to open.\n";
                exit(1);
        }  // switch ..choice
    }  // while loop
    
    // Check file flag only if manual mode is selected
    if (cmdOptions.manual && (fileFlag == false || cmdOptions.inFilename == "")) {
        cerr << ".vtt file failed to open. Please try again with proper file.\n";
        exit(1);
    }
}  // getMode()

// Function to get file info from directory
void getDirectoryInfo(const std::string &directoryPath, vector<string> &filePaths, vector<string> &fileNames, size_t &numFiles) {
    filePaths.clear();
    fileNames.clear();
        
    // Check if directory exists
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
        std::cerr << "Error: Directory does not exist or is not a directory." << std::endl;
        exit(0);
    }
    
    // Iterate through directory
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry.path())) {
            filePaths.push_back(entry.path().string());
            fileNames.push_back(entry.path().filename().string());
        }
    }
    
    numFiles = filePaths.size();
}

// Create output directory if it doesn't exist
bool createOutputDirectory(const string &dirPath) {
    std::error_code ec;
    
    if (!fs::exists(dirPath)) {
        if (!fs::create_directories(dirPath, ec)) {
            cerr << "Error creating directory " << dirPath << ": " << ec.message() << endl;
            return false;
        }
        cout << "Created output directory: " << dirPath << endl;
    }
    
    return true;
}

string changeFileExtension(const string &fileName, const string &oldExt, const string &newExt) {
    string newName = fileName;
    size_t pos = newName.rfind(oldExt);
    
    if (pos != string::npos) {
        newName.replace(pos, oldExt.length(), newExt);
    }
    
    return newName;
}

// Function to get output path for a file
string getOutputPath(const string &inputPath, const string &outputDir, const string &oldExt, const string &newExt) {
    // Extract just the filename without directory
    fs::path filePath(inputPath);
    string baseName = filePath.filename().string();
    
    // Change extension
    string newName = changeFileExtension(baseName, oldExt, newExt);
    
    // Combine with output directory
    fs::path outputPath = fs::path(outputDir) / newName;
    
    return outputPath.string();
}

int main(int argc, char* argv[]) {
    CmdOptions options;
    getMode(argc, argv, options);
    
    // Create output directory
    if (!createOutputDirectory(options.outputDir)) {
        cerr << "Failed to create output directory. Exiting." << endl;
        return 1;
    }

    if (options.manual) {
        Parser parser;

        ifstream file(options.inFilename);
        if (!file) {
            cerr << "Error: Could not open file " << options.inFilename << endl;
            return 1;
        }

        // Get output path in the output directory
        string outFilename = getOutputPath(options.inFilename, options.outputDir, ".vtt", ".txt");
        ofstream outFile(outFilename);
        if (!outFile) {
            cerr << "Error: Could not create output file " << outFilename << endl;
            return 1;
        }

        cout << "Processing: " << options.inFilename << " -> " << outFilename << endl;
        parser.parse(file, outFile);
    }
    else {
        vector<string> fileNames;
        vector<string> filePaths;
        size_t numFiles; 

        string directoryName;
        cout << "Enter file directory name: ";
        cin >> directoryName;

        getDirectoryInfo(directoryName, filePaths, fileNames, numFiles);

        if (numFiles == 0) {
            cerr << "Error: Given directory contains no files\n";
            return 1;
        }
        
        cout << "Found " << numFiles << " files" << endl;
        
        int processedCount = 0;
        for (size_t idx = 0; idx < numFiles; ++idx) {
            // Process only .vtt files
            if (filePaths[idx].substr(filePaths[idx].length() - 4) == ".vtt") {
                Parser parser;

                ifstream file(filePaths[idx]);
                if (!file) {
                    cerr << "Error: Could not open file " << filePaths[idx] << endl;
                    continue;
                }

                // Get output path in the output directory
                string outFilename = getOutputPath(filePaths[idx], options.outputDir, ".vtt", ".txt");
                ofstream outFile(outFilename);
                if (!outFile) {
                    cerr << "Error: Could not create output file " << outFilename << endl;
                    continue;
                }

                cout << "Processing: " << filePaths[idx] << " -> " << outFilename << endl;
                parser.parse(file, outFile);
                processedCount++;
            }
        }
        
        cout << "Completed processing " << processedCount << " .vtt files" << endl;
    }

    return 0;
}
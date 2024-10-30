#include "Parser.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 4) {
        cerr << "Error Usage: " << argv[0] << " <filename.vtt> <outputFile.txt>" << endl;
        exit(1);
    }

    Parser parser;

    string inFilename = argv[1];
    ifstream file(inFilename);

    string outFileName = argv[2];

    ofstream outFile(outFileName);

    string peopleFile = argv[3];

    parser.mapSpeakerInit(peopleFile);

    parser.parse(file,outFile);

    return 0;
}
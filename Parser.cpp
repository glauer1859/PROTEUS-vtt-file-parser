#include "Parser.hpp"

using namespace std;

bool Parser::validSpeaker(const string & speaker){
    bool found = false;

    // check if speaker is in our list of expected speakers
    for(const auto & name : speakers){
        found = (name == speaker)? true : false;
    }

    return found; 
}

/* void Parser::parse(istream &input, const string &output){
    //throw away the leading input lines
    string introLine;
    input >> introLine;
    getline(input,introLine);

    string prevLineSpeaker;

    // holds the timestamp of when the current speaker started talking
    string startSpeakingStamp;

    // processing the rest of the file
    while(!input.eof()){
        string lineNumber;
        string speaker;
        string lineText;
        string newStamp;

        // get rid of original line number
        getline(input,lineNumber);

        // read in when person starts speaking
        input >> newStamp;

        // remove second time stamp
        getline(input,lineNumber);

        // takes in the speaker string
        getline(input,speaker,':');

        // gets the spoken line text
        getline(input,lineText);

        if((speaker == prevLineSpeaker)){
            speakerLines[speaker].push_back(lineText);
        }
        else{
            printSection(prevLineSpeaker,startSpeakingStamp,output);
            speakerLines[prevLineSpeaker].clear();
            // update the previousLineSpeaker
            prevLineSpeaker = speaker;
            startSpeakingStamp = newStamp;
        }

    }



}*/

void Parser::parse(istream &input, ofstream &output) {
    // throw away the leading input lines
    string introLine;
    getline(input,introLine);
    getline(input, introLine);

    string prevLineSpeaker;

    // holds the timestamp of when the current speaker started talking
    string startSpeakingStamp;

    // just a variable to help things run smoothly for the first speaker
    bool firstSpeaker = true;

    // processing the rest of the file
    while (!input.eof()) {
        string lineNumber;
        string currentSpeaker;
        string lineText;
        string newStamp;
        string newline;

        // get rid of original line number
        getline(input, lineNumber);

        if(lineNumber == ""){
            break;
        }

        // read in when person starts speaking
        input >> newStamp;

        // remove second time stamp
        getline(input, lineNumber);

        // takes in the speaker string
        getline(input, currentSpeaker, ':');

        // gets the spoken line text
        getline(input, lineText);

        // removes the newline after each line
        getline(input,newline);
        
        // only runs on the first loop
        if(firstSpeaker){
            firstSpeaker = false;
            prevLineSpeaker = currentSpeaker;
            startSpeakingStamp = newStamp;
        }

        if (currentSpeaker == prevLineSpeaker) {
            speakerLines[currentSpeaker].push_back(lineText);
        } 
        else {            
            // print the lines said by the previous speaker
            printSection(prevLineSpeaker, startSpeakingStamp, output);

            speakerLines[currentSpeaker].push_back(lineText);

            // remove all lines said so far by previous speaker for next time
            speakerLines[prevLineSpeaker].clear();
            
            // update the previousLineSpeaker and new start time
            prevLineSpeaker = currentSpeaker;
            startSpeakingStamp = newStamp;
        }
    }

    // Print the last section
    if (!prevLineSpeaker.empty()) {
        printSection(prevLineSpeaker, startSpeakingStamp, output);
    }
}



void Parser::printSection(const string &speaker,const string &timestamp, ofstream &outFile){

    outFile <<"(" << timestamp << ")" << endl;
    outFile << speaker  << ": ";

    for(size_t i = 0; i < speakerLines[speaker].size(); ++i){
        outFile << (speakerLines[speaker][i].erase(0,1)).erase(speakerLines[speaker][i].size()-1) << " ";
    }
    outFile << endl << endl;
} 

void Parser::mapSpeakerInit(const string &peopleFile){

    ifstream inFile(peopleFile);
    string name;

        // initialize map with the speaker names
    while(getline(inFile,name)){
        speakerLines[name];
        speakers.push_back(name);
    }

}
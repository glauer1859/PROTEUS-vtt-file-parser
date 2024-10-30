#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Parser{
    private:   

    std::unordered_map<std::string,std::vector<std::string>> speakerLines;
    std::vector<std::string> speakers;



    public:

    void mapSpeakerInit(const std::string &peopleFile);

    bool validSpeaker(const std::string & speaker);

    void parse(std::istream &input, std::ofstream &output);

    void printSection(const std::string &speaker, const std::string &timestamp, std::ofstream &output);
};
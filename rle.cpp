#include "rle.h"

void RLE::SaveFile(std::string fileName, std::vector<std::string> lines)
{
    std::fstream file;
    file.open(fileName, std::ios_base::out);

    for(int i = 0; i < lines.size(); i++){
        std::string parsedLine = "";
        char character = lines[i][0];
        int counter = 1;
        for(int j = 1; j < lines[i].length(); j++){
            if(character == lines[i][j]){
                counter++;
            }
            else {
                parsedLine += std::to_string(counter) + character;
                character = lines[i][j];
                counter = 1;
            }
        }
        parsedLine += std::to_string(counter) + character;
        file << parsedLine;
        if(i == lines.size() - 1){
            file << '!';
        }
        else {
            file << '$';
        }
    }
    file.close();
}

std::vector<std::string> RLE::LoadFile(std::string fileName)
{
    std::fstream file;
    file.open(fileName, std::ios_base::in);
    std::string line;
    std::vector<std::string> lines;
    if(file.is_open()){
        while(std::getline(file, line)){
            if (line[0] == '#') continue;

            std::string unparsedLine = "";
            std::string number = "";
            for(int i = 0; i < line.length(); i++){
                if(line[i] >= '0' && line[i] <= '9'){
                    number += line[i];
                }
                else if(line[i] == '$' || line[i] == '!'){
                    lines.push_back(unparsedLine);
                    number = "";
                    unparsedLine = "";
                }
                else{
                    int count = 1;
                    if(number.length() > 0){
                        count = std::stoi(number);
                    }
                    for(int j = 0; j < count; j++){
                        unparsedLine += line[i];
                    }
                    number = "";
                }
            }
        }
        file.close();
    }
    return lines;
}

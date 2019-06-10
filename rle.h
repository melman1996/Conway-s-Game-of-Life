#pragma once

#include <string>
#include <fstream>
#include <vector>

class RLE
{
public:
    RLE();
    static void SaveFile(std::string, std::vector<std::string>);
    static std::vector<std::string> LoadFile(std::string);
};

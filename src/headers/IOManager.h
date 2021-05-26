/*
A static class to deal with file input and output
*/
#pragma once

#include <vector>
#include <string>

class IOManager
{
public:
    static bool readFileToBuffer(std::string filepath, std::vector<char> &buffer);
};

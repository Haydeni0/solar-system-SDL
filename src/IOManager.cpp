#include "IOManager.h"

#include <fstream>

bool IOManager::readFileToBuffer(std::string filepath, std::vector<char> &buffer)
{
    // Read the file in as binary
    std::ifstream file(filepath, std::ios::binary);
    if (file.fail())
    {
        perror(filepath.c_str());
        return false;
    }

    // Find how many bytes the file contains
    // Seek to the end
    file.seekg(0, std::ios::end);

    // Get the file size
    int file_size = file.tellg(); // How many bytes are before the location

    // Seek back to the beginning
    file.seekg(0, std::ios::beg);

    // Reduce the file size by removing any header bytes that might be present
    file_size -= file.tellg();

    // Resize the buffer vector
    buffer.resize(file_size);

    // Read file into the buffer
    file.read(&(buffer[0]), file_size);
    file.close();

    return true;
}
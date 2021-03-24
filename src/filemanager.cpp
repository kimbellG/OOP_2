#include "filemanager.h"

#include <fstream>


FileManager::FileManager(const std::string &filename)
    : in(filename)
{
}

std::string FileManager::getline()
{
    std::string result;
    std::getline(in, result);
    return result;
}


#include "filemanager.h"

#include <fstream>


FileManager::FileManager(const std::string &filename)
    : in(filename, std::ios_base::out | std::ios_base::in | std::ios_base::app)
{
    if (!in.is_open())
    {
        throw std::runtime_error("Invalid file.");
    }
}

std::string FileManager::getline()
{
    std::string result;
    std::getline(in, result);
    return result;
}

void FileManager::save_string_to_file(const std::string &value)
{
    in << value;
}

#ifndef FILEMANAGER_H
#define FILEMANAGER_H


#include <fstream>

class FileManager
{
    std::fstream in;
public:
    FileManager(const std::string &filename);

    std::string getline();
    void save_string_to_file(const std::string &value);
};

#endif // FILEMANAGER_H

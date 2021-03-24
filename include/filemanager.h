#ifndef FILEMANAGER_H
#define FILEMANAGER_H


#include <fstream>

class FileManager
{
    std::ifstream in;
public:
    FileManager(const std::string &filename);

    std::string getline();
};

#endif // FILEMANAGER_H

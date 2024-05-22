#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include<iostream>
#include<string>
#include<fstream>

class FileHandler{
private:
    std::ofstream fout;
    bool file_opened = 0;
public:
    FileHandler(const std::string& name);
    void WriteLine(const std::string& line);
    bool IsFileOpened();
    ~FileHandler();
};

#endif

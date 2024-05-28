#include"FileHandler.h"

FileHandler::FileHandler(const std::string& name){
    for(int i = 0;i<10;i++){ // retry Count
        fout.open(name,std::ios::app);
        if (!fout.is_open()) {
            std::cout<<"\nOpen File failure \n";
        }else{
            file_opened = 1;
            break;
        }
    }
}

void FileHandler::WriteLine(const std::string& line){
    fout << line << std::endl;
}

bool FileHandler::IsFileOpened(){
    return file_opened;
}

FileHandler::~FileHandler(){
    fout.close();// not necessary
}

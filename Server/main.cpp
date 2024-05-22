#include<iostream>
#include<memory>
#include<thread>

#include"Server.h"

int main(){
    std::cout<<"Server"<<std::endl;

    Server server;
    server.Run();

    return 0;

}

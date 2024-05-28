#ifndef SERVER_H
#define SERVER_H
#include<vector>
#include<thread> // not used
#include<memory>
#include"Server_Connection.h"
#include"Ts_vector.h"
#include"Mouse_Handler.h"
#include<mutex>

#define PORT 8080 // Don't use define. Move to cpp file

// That's good
class Server_Connection;
class FileHandler;

// declare members of the class vice versa
// public first
// private variables last
class Server{
private:
    Ts_vector<std::shared_ptr<Server_Connection>> ts_vector; // improve naming
    Mouse_Handler mouse;
    std::mutex mx;
private:
    void Listening();
    void MouseButtonClicksLogic();
    void MouseMoveLogic();
    void SendToAllClients(std::string& str);
public:
    Server();
    void Run();
};

#endif



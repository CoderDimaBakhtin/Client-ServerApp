#ifndef SERVER_H
#define SERVER_H
#include<vector>
#include<thread>
#include<memory>
#include"Server_Connection.h"
#include"Ts_vector.h"
#include"Mouse_Handler.h"
#include<mutex>

#define PORT 8080

class Server_Connection;
class FileHandler;

class Server{
private:
    Ts_vector<std::shared_ptr<Server_Connection>> ts_vector;
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



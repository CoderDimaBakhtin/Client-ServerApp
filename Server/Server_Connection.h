#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <string>
#include <netinet/in.h>
#include <iostream>       
#include <unistd.h>
#include <stdexcept> 
#include <mutex>

class Server_Connection{
private:
    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    bool Client_Connected = 0;
    const uint16_t PORT;
public:
    Server_Connection(const uint16_t PORT_);
    bool PrepareToAccept();
    void Accept();
    std::string Read();
    void Send(const std::string& message);
    bool Is_Connected();
    ~Server_Connection();
};


#endif
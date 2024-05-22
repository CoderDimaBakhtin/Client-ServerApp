#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include<iostream>
#include<arpa/inet.h>
#include<string>

class Client_connection{
private:
    int client_fd;
    struct sockaddr_in serv_addr;
    bool Client_Connected = 0;
public:
    Client_connection(uint16_t PORT,const std::string& IpAdress);
    void Connect();
    void Send(const std::string& message);
    std::string Read();
    bool Is_Connected();
    ~Client_connection();
};

#endif

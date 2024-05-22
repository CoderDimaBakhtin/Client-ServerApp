#include"Client_Connection.h"
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>

Client_connection::Client_connection(uint16_t PORT,const std::string& IpAdress){
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout<<"\n Socket creation error \n";
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, const_cast<char*>(IpAdress.c_str()), &serv_addr.sin_addr)<= 0) {
        std::cout<<"\nInvalid address/ Address not supported \n";
    }
}

void Client_connection::Connect(){
    int status;
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))< 0) {
        std::cout<<"\nConnection Failed \n";
    }else{
        Client_Connected = 1;
    }
}

void Client_connection::Send(const std::string& message){
    if(Client_Connected){
        send(client_fd, const_cast<char*>(message.c_str()), message.size(), 0);
    }
}

std::string Client_connection::Read(){
    if(Client_Connected){
        int valread;
        char buffer[1024] = { 0 };
        valread = read(client_fd, buffer,1024 - 1);
        if(valread == -1){

        }
        std::string message(buffer);
        return message;
    }
    return "";
}

bool Client_connection::Is_Connected(){
    return Client_Connected;
}

Client_connection::~Client_connection(){
    close(client_fd);
}

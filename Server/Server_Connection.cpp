#include"Server_Connection.h"

Server_Connection::Server_Connection(const uint16_t PORT_):PORT(PORT_){
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
}

bool Server_Connection::PrepareToAccept(){
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout<<"\nsocket failed \n";
        return false;
    }
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt))){
        std::cout<<"\nsetsockopt failed \n";
        return false;
    }
    if (bind(server_fd, (struct sockaddr*)&address,sizeof(address))< 0){
        std::cout<<"\nbind failed \n";
        return false;
    }
    if (listen(server_fd, 1) < 0){
        std::cout<<"\nlisten failure \n";
        return false;
    }
    return true;
}

void Server_Connection::Accept(){
    socklen_t addrlen = sizeof(address);
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address,&addrlen))< 0){
        std::cout<<"\nAccept failure \n";
    }else{
        Client_Connected = 1;
    }
}

std::string Server_Connection::Read(){ // get rid of nesting
    if (!Client_Connected)
        return "";

    ssize_t valread = read(new_socket, buffer, sizeof(buffer) - 1);
    if (valread == -1) {//Reading Error
        std::cout<<"\nReading Error\n";
        return "";
    }

    if (valread == 0) {
        Client_Connected = 0;
        std::cout<<"\nConnection closed by the Client\n";

        return "";
    }

    std::string str(buffer, valread); // provide size of the buffer
    return str;

    // if(Client_Connected){
    //     ssize_t valread = read(new_socket, buffer, sizeof(buffer) - 1);
    //     if (valread == -1) {//Reading Error
    //         std::cout<<"\nReading Error\n";
    //         return "";
    //     } else if (valread == 0) {
    //         Client_Connected = 0;
    //         std::cout<<"\nConnection closed by the Client\n";
            
    //         return "";
    //     }
    //     std::string str(buffer); // provide size of the buffer
    //     return str;
    // }
    // return "";
}

void Server_Connection::Send(const std::string& message){
    if(Client_Connected){
        send(new_socket, const_cast<char*>(message.c_str()), message.size(), 0);
    }
}


bool Server_Connection::Is_Connected(){
    return Client_Connected;
}

Server_Connection::~Server_Connection(){
    close(new_socket);
    close(server_fd);
}
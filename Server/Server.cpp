#include "Server.h"
#include <filesystem>
#include <atomic>
#include <csignal>
#include"Ts_vector.h"

std::atomic<bool> exit_thread_flag{ false }; // should be member of the class.

Server::Server(){
    if(!mouse.IsMouseHandled()){
        exit_thread_flag = true;
    }
}

void Server::Listening(){ // AcceptClients()
    while(!exit_thread_flag){
        std::shared_ptr<Server_Connection> connection = std::make_shared<Server_Connection>(PORT); //use auto
        if(connection->PrepareToAccept()){
            std::cout<<"\nAccept...\n";
            connection->Accept();
            if(connection->Is_Connected()){
                std::cout<<"\nAccepted\n";
                ts_vector.push_back(connection);
            }
        }
    }
}

void Server::Run(){
    signal(SIGINT, [](int signal){exit_thread_flag = true;});

    std::thread t(&Server::Listening, this); // give proper names to threads
    std::thread t1(&Server::MouseButtonClicksLogic, this);
    std::thread t2(&Server::MouseMoveLogic, this);

    while(!exit_thread_flag){
        for(size_t i=0;i<ts_vector.size();i++){
            if(ts_vector[i]->Is_Connected()){
                [[maybe_unused]] std::string received_message = ts_vector[i]->Read();
                if(!ts_vector[i]->Is_Connected()){
                    ts_vector.delete_element(i);
                }
                if(received_message=="OK"){
                    //FeedbackHandler(m);
                }
            }
        }
    }
    std::cout<<"\nServer_End\n";
    
    t.detach();
    t1.detach();
    t2.detach(); // Join threads
}

void Server::MouseButtonClicksLogic(){
    std::string str;
    while(!exit_thread_flag){
        str = mouse.GetMouseButtonClick();
        SendToAllClients(str);
    }
}

void Server::MouseMoveLogic(){
    std::string str;
    while(!exit_thread_flag){
        std::chrono::milliseconds delay(50); 
        std::this_thread::sleep_for(delay);
        str = mouse.GetCoordinates()+"!"+mouse.GetRelativeCoordinates();
        SendToAllClients(str);
    }
}

void Server::SendToAllClients(std::string& str){ // const
    for(size_t i=0;i<ts_vector.size();i++){
        if(ts_vector[i]->Is_Connected()){
            ts_vector[i]->Send(str);
        }
    }
}
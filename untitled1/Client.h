#ifndef CLIENT_H
#define CLIENT_H

#include<memory>
#include"Client_Connection.h"
#include"FileHandler.h"
#include"imagesignalsender.h"
#include"labelhandler.h"

class Client{
private:
    std::shared_ptr<Client_connection> connection;
    std::shared_ptr<FileHandler> file; // why shared_ptr?
    bool End_Program = 0;
    bool flag_standart = true;
    bool flag_left= true;
    bool flag_right= true;
private:
    enum class Buttonstate{
        // Why such numbers used?
        LeftMouseClick =11,
        RightMouseClick =21,
        LeftMouseUp =12,
        RightMouseUp =22,
        None =0
    };
    Buttonstate Parse_message(const std::string& received_message);
    void PrintImage(ImageSignalSender& SignalHandler,std::string& received_message);
    void SplitMessages(const std::string&, std::string& , std::string&);
public:
    Client(uint16_t PORT,const std::string& IpAdress);
    void Run(ImageSignalSender& SignalHandler,LabelHandler& labelhandler);

};

#endif // CLIENT_H

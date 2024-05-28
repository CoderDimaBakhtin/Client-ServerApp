#include"Client.h"
#include<atomic>
#include<csignal>

std::atomic<bool> exit_thread_flag{ false };

Client::Client(uint16_t PORT,const std::string& IpAdress){
    connection = std::make_shared<Client_connection>(PORT,IpAdress);
    file = std::make_shared<FileHandler>("file.txt");
    if(!file->IsFileOpened()){
        exit_thread_flag = true;
    }
    connection->Connect();
}

void Client::SplitMessages(const std::string& received_message, std::string& string_to_write_to_file, std::string& string_to_write_to_screen){
    int flag = 0;
    string_to_write_to_file = ""; // .clear()
    string_to_write_to_screen = "";
    for(int i = 0;i<received_message.size();i++){
        if(flag==0 && received_message[i]=='!'){ // parse it in more understandable way
            flag = 1;
        }
        if(flag == 0){
            string_to_write_to_file+=received_message[i];
        }else{
            if(received_message[i]!='!'){
                string_to_write_to_screen+=received_message[i];
            }
        }
    }
}

void Client::Run(ImageSignalSender& SignalHandler,LabelHandler& labelhandler){ // TODO add time
    file->WriteLine("=================================");
    signal(SIGINT, [](int signal){std::cout<<"\nCtrlC Handler\n";exit_thread_flag = true;}); // awesome
    int Fpscounter = 0;
    std::string string_to_write_to_file = ""; // remove string from name. fileOutput
    std::string string_to_write_to_screen = "";
    while(true){
        std::string received_message = connection->Read();
        if(received_message !=""){
            SplitMessages(received_message,string_to_write_to_file,string_to_write_to_screen);
            file->WriteLine(string_to_write_to_file);
            PrintImage(SignalHandler,string_to_write_to_file);

            if(Fpscounter<3){ // its better to use sleep()
                Fpscounter++;
            }else{
                Fpscounter = 0;
                labelhandler.setLabelText(QString::fromUtf8(string_to_write_to_screen.c_str()));
            }

            if(!exit_thread_flag){
                connection->Send("OK");
            }else{
                connection->Send("Biy from client"); // bye
                break;
            }
        }
    }
}

Client::Buttonstate Client::Parse_message(const std::string& received_message){
    for(int i = 0;i<received_message.size();i++){
        // button ;
        // action;
        switch (received_message[i]) {
        case 'L':
            // button = left;
            // i++;
            if(received_message[i+2] == 'K'){ // out of range exception
                return Buttonstate::LeftMouseClick;
            }
            if(received_message[i+2] == 'U'){
                return Buttonstate::LeftMouseUp;
            }
            break;
        // case 'K':
        //     action = clicked;
        case 'R':
            if(received_message[i+2] == 'K'){
                return Buttonstate::RightMouseClick;
            }
            if(received_message[i+2] == 'U'){
                return Buttonstate::RightMouseUp;
            }
            break;
        }
    }
    return Buttonstate::None;
}

void Client::PrintImage(ImageSignalSender& SignalHandler,std::string& received_message){
    switch (Parse_message(received_message)) {
    // very complicated logic of states, can be improved
    // remove copy paste here
    case Buttonstate::LeftMouseClick:
        flag_left = false;
        emit SignalHandler.setImageSignal("mouseLeft.png");
        emit SignalHandler.showImageSignal(); // qml does it already
        break;
    case Buttonstate::LeftMouseUp:
        flag_left = true;
        if(flag_right){
            emit SignalHandler.hideImageSignal();
        }else{
            emit SignalHandler.setImageSignal("mouseRight.png");
            emit SignalHandler.showImageSignal();
        }
        break;
    case Buttonstate::RightMouseClick:
        flag_right = false;
        emit SignalHandler.setImageSignal("mouseRight.png");
        emit SignalHandler.showImageSignal();
        break;
    case Buttonstate::RightMouseUp:
        flag_right = true;
        if(flag_left){
            emit SignalHandler.hideImageSignal();
        }else{
            emit SignalHandler.setImageSignal("mouseLeft.png");
            emit SignalHandler.showImageSignal();
        }
        break;
    case Buttonstate::None:
        break;
    }
    if(flag_left&&flag_right){
        emit SignalHandler.setImageSignal("mouseStandart.png");
        emit SignalHandler.showImageSignal();
    }
    if(!(flag_left||flag_right)){
        emit SignalHandler.setImageSignal("mouseBoth.png");
        emit SignalHandler.showImageSignal();
    }
}





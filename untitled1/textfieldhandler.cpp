#include "textfieldhandler.h"

void TextFieldHandler::receiveText(const QString &text) {
    std::string stringtext=text.toStdString();
    int flag = 0;
    std::string port_str="";

    // npos
    // ip = text.substr(0, text.find(" "));
    // port = ....

    for(int i = 0;i<stringtext.size();i++){
        // Awful logic, simlify it
        if(flag == 0&&stringtext[i]==' '){
            flag = 1;
        }
        if(flag == 0){
            IpAdress+=stringtext[i];
        }else{
            if(stringtext[i]!=' '){
                port_str+=stringtext[i];
            }
        }
    }

    // use from_chars()
    port = static_cast<uint16_t>(std::stoul(port_str)); // exception not handled
}
void TextFieldHandler::SetFieldState(bool state){
    m_buttonVisible = state;
}
bool TextFieldHandler::GetFieldState(){
    return m_buttonVisible;
}

uint16_t TextFieldHandler::GetPort(){
    return port;
}
std::string TextFieldHandler::GetIpAdress(){
    return IpAdress;
}

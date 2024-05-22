#include "textfieldhandler.h"

void TextFieldHandler::receiveText(const QString &text) {
    std::string stringtext=text.toStdString();
    int flag = 0;
    std::string port_str="";
    for(int i = 0;i<stringtext.size();i++){
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
    port = static_cast<uint16_t>(std::stoul(port_str));
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

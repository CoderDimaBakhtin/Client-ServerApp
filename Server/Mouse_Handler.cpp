#include"Mouse_Handler.h"

//Passing a command to the shell command line across a newly created pipe and returning the result of the command
std::string Mouse_Handler::CommandToPipe(const char* command) { 
    std::array<char, 128> buffer; 
    std::string result; 
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose); 
    if (!pipe) { 
        throw std::runtime_error("popen() failed!"); 
    } 
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { 
        result += buffer.data(); 
    } 
    return result; 
}

//Preparation work before mouse reading
Mouse_Handler::Mouse_Handler(){
    for(int i = 0;i<10;i++){
        fd = open(pDevice, O_RDWR);
        if(fd == -1){
            printf("\nMouseERROR Opening %s\n", pDevice);   
        }else{
            MouseHandled = 1;
        }
    }
    if(MouseHandled){
        bytes = read(fd, data, sizeof(data));
        if((data[0]& 0x4)==4){
            Middleflag = 1;
        }else{
            Middleflag = 0;
        }
    }
}

std::string Mouse_Handler::GetCoordinates(){
    std::string str = CommandToPipe("xdotool getmouselocation --shell");
    std::string str2;
    int i = 0;
    while(str[i]!='S'){//We need to extract all information before some "moment"
        if(str[i]=='\n'){
            str2+=' ';
        }else{
            str2+=str[i];
        }
        i++;
    }
    return str2;
}

std::string Mouse_Handler::GetRelativeCoordinates(){
    return "xrel="+std::to_string(x)+" yrel="+std::to_string(y);
}

std::string Mouse_Handler::GetMouseButtonClick(){
    while(true){
        bytes = read(fd, data, sizeof(data));
        if(bytes > 0){
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;

            x = data[1];
            y = data[2];
            //
            if(left==1 && Leftflag == 0){
                Leftflag = 1;
                return GetCoordinates()+" LMK(Left Mouse click)";
            }
            if(left==0 && Leftflag == 1){
                Leftflag = 0;
                return GetCoordinates()+" LMU(Left Mouse UP)";
            }

            if(right==2 && Rightflag == 0){
                Rightflag = 1;
                return GetCoordinates()+" RMK(Right Mouse click)";
            }
            if(right==0 && Rightflag == 1){
                Rightflag = 0;
                return GetCoordinates()+" RMU(Right Mouse UP)";
            }
        }
    }
}

bool Mouse_Handler::IsMouseHandled(){
    return MouseHandled;
}
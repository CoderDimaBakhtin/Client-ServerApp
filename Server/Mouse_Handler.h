#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

#include <unistd.h> 
#include <string>
#include <fcntl.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <linux/input.h>

class Mouse_Handler{
private:
    int fd, bytes;
    unsigned char data[4]={0,0,0,0};
    const char *pDevice = "/dev/input/mice";
    int left, middle, right;
    signed char x, y;
    bool Middleflag = 0;
    bool Leftflag = 0;
    bool Rightflag = 0;
    bool MouseHandled = 0;
private:
    std::string CommandToPipe(const char* cmd);
public:
    Mouse_Handler();
    std::string GetCoordinates();
    std::string GetRelativeCoordinates();
    std::string GetMouseButtonClick();
    bool IsMouseHandled();
};

#endif
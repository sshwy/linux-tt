/***
 * author: @sshwy
 * name: scankb.cpp
 * description: 用于处理键盘监听的模块
 */
#ifndef _SCANKB_H_
#define _SCANKB_H_
#include <stdio.h>
#include <termio.h>

// scanKeyboard 每次是读取一个字符，没有输入就等待
int scanKeyboard() {
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    new_settings= stored_settings;
    new_settings.c_lflag&= (~ICANON);
    new_settings.c_cc[VTIME]= 0;
    tcgetattr(0, &stored_settings);
    new_settings.c_cc[VMIN]= 1;
    tcsetattr(0, TCSANOW, &new_settings);

    in= getchar();

    tcsetattr(0, TCSANOW, &stored_settings);
    return in;
}

#endif

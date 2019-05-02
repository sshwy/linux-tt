/**
 * author: @sshwy
 * name: status.cpp
 * description: 游戏的状态结构体
 */
#ifndef _STATUS_H_
#define _STATUS_H_
#include "display.h"
#include "signal.h"
#include <cstdio>
struct Game {
    int status;
    /*
     * 1:home
     * 2:exit
     * 3:menu
     * 4:about
     * 5:start
     * 6:input
     * 7:incorrect
     * 8:finish
     * 0:error
     */
    Data data;
    //初始化
    Game(int _status= 1) {
        status= _status;
    }
    void display() {  //命令行界面显示
        if(status == 1)
            display_1();
        else if(status == 3)
            display_3();
        else if(status == 5)
            display_5(data);
        else if(status == 6)
            display_6(data);
        else if(status == 7)
            display_7(data);
        else if(status == 8)
            display_8();
        else
            info("Still developing...");
    }
};
#endif

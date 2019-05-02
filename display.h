#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "signal.h"
#include <cstdio>
#include <cstdlib>
#include <string>

struct Data {             //不同状态下的卫星数据也不一样
    std::string content;  // 6:input
    int cor_ch;           // 6:input,7:incorrect
    int incor_ch;         // 7:incorrect
    int lastkey;          //上一次按下的键
};

const std::string path= "./src/";

void display_1() {  // 1:home
    puts("\033c");  //清屏
    puts("");
    sig("[ home ]");
    puts("[M] menu");
    puts("[A] about");
    puts("[ESC] exit");
}
void display_3() {  // menu
    puts("\033c");  //清屏
    puts("");
    sig("\r[ menu ]");
    puts("[ESC] home");
    puts("\n======= list =======");

    system(("ls " + path + " > .menu").c_str());  //执行命令，写入文件

    FILE * f= fopen(".menu", "r");
    char name[100][50];  //最多100个文件
    int tot= 0;
    while(~fscanf(f, "%s", name[tot]))
        printf("[%d]%s\n", tot, name[tot]), ++tot;
    fclose(f);
}
void display_5(Data d) {  // start
    puts("\033c");        //清屏
    sig("\r[ start ]");
    puts("Prese any key to start");
    puts("Or press [ESC] to exit");

    info("=======Contents=======");
    printf("\033[s");  //保存光标位置
    printf("\033[4m");
    for(int i= 0; d.content[i]; i++) putchar(d.content[i]);
    printf("\033[u");  //恢复光标位置
}
void display_6(Data d) {  // input
    puts("\033c");        //清屏
    info("=======Contents=======");
    for(int i= 0; i <= d.cor_ch; i++) putchar(d.content[i]);
    printf("\033[4m");
    printf("\033[s");  //保存光标位置
    for(int i= d.cor_ch + 1; d.content[i]; i++) putchar(d.content[i]);
    printf("\033[u");
}
void display_7(Data d) {  // incorrect
    puts("\033c");        //清屏
    info("=======Contents=======");
    for(int i= 0; i <= d.cor_ch; i++) putchar(d.content[i]);
    printf("\033[31m\033[4m");
    for(int i= d.cor_ch + 1; i<=d.incor_ch; i++) putchar(d.content[i]);
    printf("\033[0m\033[4m");
    printf("\033[s");  //保存光标位置
    for(int i= d.incor_ch + 1; d.content[i]; i++) putchar(d.content[i]);
    printf("\033[u");
}
void display_8(){//finish
    puts("\033c");        //清屏
    puts("You Down!");
    puts("Press [ESC] to go back to menu");
}
#endif

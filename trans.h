/**
 * author: @sshwy
 * name: trans.cpp
 * description: 状态转移函数
 */
#ifndef _TRANS_H_
#define _TRANS_H_
#include "status.h"
#include <cstring>
#define HOME 1
#define EXIT 2
#define MENU 3
#define ABOUT 4
#define START 5
#define INPUT 6
#define INCORRECT 7
#define FINISH 8
#define ERROR 0

Game (*game_trans[10][300])(Game);  //指向Game(Game)的指针二维数组

Game home(Game g) {
    return g.status= HOME, g;
}
Game menu(Game g) {
    return g.status= MENU, g;
}
Game exit(Game g) {  //任何指向状态exit的函数
    return g.status= EXIT, g;
}
Game about(Game g) {
    return g.status= ABOUT, g;
}
Game self(Game g) {
    return g;
}
Game start(Game g) {
    //读取菜单列表
    char name[100][50];  //最多100个文件
    int tot= 0;

    FILE * f= fopen(".menu", "r");
    while(~fscanf(f, "%s", name[tot])) ++tot;
    fclose(f);

    if(g.data.lastkey - '0' >= tot) {
        info("No such file!");
        printf("g.data.lastkey:%d\n", g.data.lastkey);
        return g;
    }
    if(g.data.lastkey < '0') return g;  //不触发任何转移

    f= fopen((path + name[g.data.lastkey - '0']).c_str(), "r");
    char content[2000], c;  //打字的内容
    int l= -1;
    while((c= fgetc(f)) != EOF) content[++l]= c;
    content[++l]= '\0';  //尾部结束字符
    fclose(f);

    g.data.content= content;
    g.status= START;
    g.data.cor_ch= -1;
    g.data.incor_ch= -1;
    return g;
}
Game input(Game g) {
    if(g.status == START) return g.status= INPUT, g;
    g.status= INPUT;
    int & cur= g.data.cor_ch;
    int & key= g.data.lastkey;
    if(key == 127) {
        if(cur >= 0) cur--;  //退格
        return g;
    }
    if(g.data.content[cur + 1] == key)
        cur++;  //成功匹配
    else {
        g.data.incor_ch= cur + 1;  //输入错误
        g.status= INCORRECT;
        return g;
    }
    if(cur + 2 == (int)g.data.content.size()) {
        g.status= FINISH;
        return g;
    }
    return g;
}
Game incorrect(Game g) {
    int & cur= g.data.incor_ch;
    int & key= g.data.lastkey;
    if(key == 127) {
        if(cur >= 0) cur--;  //退格
        if(cur <= g.data.cor_ch) g.status= INPUT;
        return g;
    }
    cur++;
    return g;
}
Game finish(Game g) {
    return g.status= FINISH, g;
}
void trans_init() {
    //全体初始化为self
    for(int i= 0; i < 9; i++)
        for(int j= 0; j < 256; j++) game_trans[i][j]= self;
    // home
    for(int i= 0; i < 256; i++) {
        if(i == 'a')
            game_trans[HOME][i]= about;
        else if(i == 'm')
            game_trans[HOME][i]= menu;
        else
            game_trans[HOME][i]= self;
    }
    // menu
    for(int i= 0; i < 256; i++) game_trans[MENU][i]= start;
    game_trans[MENU][(int)'h']= home;
    // start
    for(int i= 0; i < 256; i++) game_trans[START][i]= input;
    // input
    for(int i= 0; i < 256; i++) game_trans[INPUT][i]= input;
    // incorrect
    for(int i= 0; i < 256; i++) game_trans[INCORRECT][i]= incorrect;
    //针对ESC键的重设
    for(int i= 0; i < 9; i++) game_trans[i][27]= exit;  // ESC
    game_trans[MENU][27]= home;
    game_trans[START][27]= menu;
    game_trans[ABOUT][27]= home;
    game_trans[FINISH][27]= home;
    game_trans[INPUT][27]= menu;
    game_trans[INCORRECT][27]= menu;
    game_trans[FINISH][27]= menu;
}
#endif

#include "scankb.h"
#include "signal.h"
#include "status.h"
#include "trans.h"
#include <cstdio>

Game g;
int main() {
    trans_init();
    printf("Welcome!");
    while(g.status != 2) {
        g.display();
        int key= scanKeyboard();
        // printf("\rkey:%d\n", key);
        g.data.lastkey= key;
        g= game_trans[g.status][key](g);
        // printf("g.status:%d\n", g.status);
    }
    sig("\rGoodBye!");
    int key= scanKeyboard();
    printf("\rkey:%d\n", key);
    return 0;
}

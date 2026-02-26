#include "DifficultMode.h"
#include "EasyNormal.h"
#include "music.h"
using namespace std;
int main() {
    initWindow(1000, 600);

    int status;
    player p;
    
    bgSound();
    while ((status = mainMenu()) != 4) {
        bgSound();
        switch (status)
        {
        case 0:
            getPlayerInfo(p);
            easyMode(p);
            break;
        case 1:
            getPlayerInfo(p);
            normalMode(p);
            break;
        case 2:
            getPlayerInfo(p);
            difficultMode(p);
            break;
        case 3:
            readLeaderBoard();
            break;
        default:
            break;
        }
    }
}
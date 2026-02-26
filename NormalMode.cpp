#include "EasyNormal.h"
#include <iostream>
using namespace std;

char bg2[20][41];

void initBoard2(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGHT2; i++) { // gan vi tri cho tung o mot
        board[i] = new CELL_1[BOARDWIDTH2];
        for (int j = 0; j < BOARDWIDTH2; j++) {
            board[i][j].j = j;
            board[i][j].i = i;
        }
    }

    int flagNum = (BOARDWIDTH2 * BOARDHEIGHT2) / 2;
    while (flagNum) { // gan ky tu cho tung o mot
        int index, time = 2;
        char c = 65 + rand() % 26;
        while (time) { // gan 1 ky tu cho 2 o
            index = rand() % 40;
            if (board[index / 8][index % 8].c == ' ') {
                board[index / 8][index % 8].c = c;
                time--;
            }
        }
        flagNum--;
    }
}

void deleteBoard2(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGHT2; i++) {
        for (int j = 0; j < BOARDWIDTH2; j++) {
            if (board[i][j].isValid) {
                board[i][j].deleteBox();
                if (j < 4) displayBackground(bg2, j, i);
                Sleep(200);
            }
        }
    }

    for (int i = 0; i < BOARDHEIGHT2; i++) {
        delete[]board[i];
    }
    delete[]board;
}

void renderBoard2(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGHT2; i++) {
        for (int j = 0; j < BOARDWIDTH2; j++) {
            board[i][j].drawBox(112);
        }
    }
}
// di chuyen
void move2(CELL_1** board, position& pos, int& status, player& p, position selectedPos[], int& couple) {
    int temp, key;
    temp = _getch();
    if (temp && temp != 224) {
        if (temp == ESC_KEY) {
            status = 2;
        }
        else if (temp == ENTER_KEY) {
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {
                board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                Sleep(500);

                board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                wrongSound();
                p.life--;
                goToXY(70, 0);
                cout << "Life: " << p.life;
            }
            else {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                board[pos.y][pos.x].isSelected = 1;
                couple--;

                if (couple == 0) {
                    if (board[selectedPos[0].y][selectedPos[0].x].c == board[selectedPos[1].y][selectedPos[1].x].c) {
                        if (allcheck2(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x)) {
                            p.point += 20;
                            correctSound();
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            board[selectedPos[0].y][selectedPos[0].x].drawBox(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(40);
                            Sleep(500);

                            board[selectedPos[0].y][selectedPos[0].x].isValid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox();
                            if (selectedPos[0].x < 4) displayBackground(bg2, selectedPos[0].x, selectedPos[0].y);

                            board[selectedPos[1].y][selectedPos[1].x].isValid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox();
                            if (selectedPos[1].x < 4) displayBackground(bg2, selectedPos[1].x, selectedPos[1].y);
                        }
                        else {
                            wrongSound();
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                            Sleep(500);

                            p.life--;
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    }
                    else {
                        wrongSound();
                        board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                        board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                        Sleep(500);

                        p.life--;
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }
                    board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };
                }
            }
        }
    }
    else //neu la dau mui ten
    {
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) // ktra xem o nay co dang duoc chon hay khong
            board[pos.y][pos.x].isSelected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < BOARDWIDTH2; i++) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH2; i++) {
                for (int j = BOARDHEIGHT2 - 1; j > pos.y; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) {
                for (int j = BOARDHEIGHT2 - 1; j > pos.y; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            break;
        case KEY_DOWN:
            for (int i = pos.x; i < BOARDWIDTH2; i++) {
                for (int j = pos.y + 1; j < BOARDHEIGHT2; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGHT2; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH2; i++) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }
            break;
        case KEY_LEFT:
            for (int i = pos.y; i >= 0; i--) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT2; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH2 - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT2; i++) {
                for (int j = BOARDWIDTH2 - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
            break;
        case KEY_RIGHT:
            for (int i = pos.y; i >= 0; i--) {
                for (int j = pos.x + 1; j < BOARDWIDTH2; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT2; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH2; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT2; i++) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
        default:
            break;
        }
    }
}

void normalMode(player& p) {
    srand(time(0));
    getBackground(bg2);

    CELL_1** board = new CELL_1 * [BOARDHEIGHT2];
    initBoard2(board);

    goToXY(10, 0);
    cout << "Name: " << p.name;
    goToXY(40, 0);
    cout << "Point: " << p.point;
    goToXY(70, 0);
    cout << "Life: " << p.life;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    goToXY(112, 4);
    cout << "Rules:";
    goToXY(100, 6);
    cout << "The Pikachu Puzzle Game includes";
    goToXY(100, 7);
    cout << "a board of multiple cells,";
    goToXY(100, 8);
    cout << "each of which presents a figure.";
    goToXY(100, 9);
    cout << "The player finds and matches";
    goToXY(100, 10);
    cout << "a pair of cells that contain the";
    goToXY(100, 11);
    cout << "same figure and connect each other";
    goToXY(100, 12);
    cout << "in some particular pattern.";
    goToXY(100, 13);
    cout << "A legal match will make the";
    goToXY(100, 14);
    cout << "two cells disappear. The game ends";
    goToXY(100, 15);
    cout << "when all matching pairs are found.";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    goToXY(100, 18);
    cout << "Press arrow key to move";
    goToXY(100, 20);
    cout << "Press Enter to choose";
    goToXY(100, 22);
    cout << "Press ESC to quit";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    stopBgSound();

    position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    position curPosition{ 0, 0 };
    int status = 0; //0. dang choi game
                    //1. het game
                    //2. nguoi choi chon thoat

    while (!status && p.life) {
        board[curPosition.y][curPosition.x].isSelected = 1;

        renderBoard2(board);

        move2(board, curPosition, status, p, selectedPos, couple);

        if ((!checkValidPairs2(board))) status = 1;
            
    }

    renderBoard2(board);
    deleteBoard2(board);
    Sleep(500);
    system("cls");

    if (p.life && status == 1) {
        displayStatus(1);
        goToXY(50, 17);
        char c;
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y') normalMode(p);
        else writeLeaderBoard(p);
    }
    else if (p.life == 0) {
        displayStatus(0);
        writeLeaderBoard(p);
        Sleep(2000);
    }
    system("cls");
}
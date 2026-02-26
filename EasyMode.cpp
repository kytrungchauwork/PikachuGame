#include "EasyNormal.h"
#include <iostream>
#include "music.h"
#include <windows.h>
#include <cmath>


using namespace std;

char bg[20][41];

void initBoard(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGHT1; i++) { // gan vi tri cho tung o mot
        board[i] = new CELL_1[BOARDWIDTH1];
        for (int j = 0; j < BOARDWIDTH1; j++) {
            board[i][j].j = j;
            board[i][j].i = i;
        }
    }

    int flagNum = (BOARDWIDTH1 * BOARDHEIGHT1) / 2;
    while (flagNum) { // gan ky tu cho tung o mot
        int index, time = 2;
        char c = 65 + rand() % 26;
        while (time) { // gan 1 ky tu cho 2 o
            index = rand() % 24;
            if (board[index / 6][index % 6].c == ' ') {
                board[index / 6][index % 6].c = c;
                time--;
            }
        }
        flagNum--;
    }
}

void deleteBoard(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGHT1; i++) {
        for (int j = 0; j < BOARDWIDTH1; j++) {
            if (board[i][j].isValid) {
                board[i][j].deleteBox();
                if (j < 4) displayBackground(bg, j, i);
                Sleep(200);
            }
        }
    }

    for (int i = 0; i < BOARDHEIGHT1; i++) {
        delete[]board[i];
    }
    delete[]board;
}

void renderBoard(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGHT1; i++) {
        for (int j = 0; j < BOARDWIDTH1; j++) {
            board[i][j].drawBox(112);
        }
    }
}


void move(CELL_1** board, position& pos, int& status, player& p, position selectedPos[], int& couple) {
    int temp, key;
    temp = _getch();
    if (temp && temp != 224) { // nếu không phải là phím mũi tên
        if (temp == ESC_KEY) { // nếu là phím ESC
            status = 2;
        }
        else if (temp == ENTER_KEY) { // nếu là phím Enter
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {
                board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                Sleep(500);
                wrongSound();
                board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                p.life--;
                goToXY(70, 0);
                cout << "Life: " << p.life;
            } // kiểm tra lặp lại
            else {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                board[pos.y][pos.x].isSelected = 1;
                couple--;

                if (couple == 0) { // nếu đã chọn 1 cặp
                    if (board[selectedPos[0].y][selectedPos[0].x].c == board[selectedPos[1].y][selectedPos[1].x].c) {  // nếu cặp này hợp nhau
                        if (allcheck(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x)) {
                            p.point += 20;
                            correctSound();
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            board[selectedPos[0].y][selectedPos[0].x].drawBox(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(40);
                            Sleep(500);

                            board[selectedPos[0].y][selectedPos[0].x].isValid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox();
                            if (selectedPos[0].x < 4) displayBackground(bg, selectedPos[0].x, selectedPos[0].y);

                            board[selectedPos[1].y][selectedPos[1].x].isValid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox();
                            if (selectedPos[1].x < 4) displayBackground(bg, selectedPos[1].x, selectedPos[1].y);
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
                    // trả về nơi sản xuất
                    board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < BOARDHEIGHT1; i++) {
                        for (int j = pos.x; j < BOARDWIDTH1; j++) {
                            if (board[i][j].isValid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i <= pos.y; i++) { // chuyển đến CELL_1 ở trên
                        for (int j = 0; j <= pos.x; j++) {
                            if (board[i][j].isValid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    else //neu la dau mui ten
    {
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) // ktra xem o nay co dang duoc chon hay khong
            board[pos.y][pos.x].isSelected = 0;
        switch (key = _getch()) {
        case KEY_UP:
            for (int i = pos.x; i < BOARDWIDTH1; i++) {
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

            for (int i = pos.x; i < BOARDWIDTH1; i++) {
                for (int j = BOARDHEIGHT1 - 1; j > pos.y; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) {
                for (int j = BOARDHEIGHT1 - 1; j > pos.y; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            break;
        case KEY_DOWN:
            for (int i = pos.x; i < BOARDWIDTH1; i++) {
                for (int j = pos.y + 1; j < BOARDHEIGHT1; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGHT1; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH1; i++) {
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

            for (int i = pos.y + 1; i < BOARDHEIGHT1; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH1 - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT1; i++) {
                for (int j = BOARDWIDTH1 - 1; j > pos.x; j--) {
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
                for (int j = pos.x + 1; j < BOARDWIDTH1; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT1; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH1; j++) {
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

            for (int i = pos.y + 1; i < BOARDHEIGHT1; i++) {
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

void easyMode(player& p) {
    
    // Khởi tạo ngẫu nhiên
    srand(time(0));

    // Lấy hình nền và phát âm thanh nền
    getBackground(bg);
    bgSound();
    CELL_1** board = new CELL_1 * [BOARDHEIGHT1];
    initBoard(board);

    // Hiển thị thông tin ban đầu
    goToXY(10, 0);
    cout << "Name: " << p.name;
    goToXY(40, 0);
    cout << "Point: " << p.point;
    goToXY(70, 0);
    cout << "Life: " << p.life;

    // Hiển thị luật chơi
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    goToXY(92, 4);
    cout << "Rules:";
    goToXY(80, 6);
    cout << "The Pikachu Puzzle Game includes";
    goToXY(80, 7);
    cout << "a board of multiple cells,";
    goToXY(80, 8);
    cout << "each of which presents a figure.";
    goToXY(80, 9);
    cout << "The player finds and matches";
    goToXY(80, 10);
    cout << "a pair of cells that contain the";
    goToXY(80, 11);
    cout << "same figure and connect each other";
    goToXY(80, 12);
    cout << "in some particular pattern.";
    goToXY(80, 13);
    cout << "A legal match will make the";
    goToXY(80, 14);
    cout << "two cells disappear. The game ends";
    goToXY(80, 15);
    cout << "when all matching pairs are found.";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    goToXY(80, 18);
    cout << "Press arrow key to move";
    goToXY(80, 20);
    cout << "Press Enter to choose";
    goToXY(80, 22);
    cout << "Press ESC to quit";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    
    stopBgSound();

    position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    position curPosition{ 0, 0 };
    int status = 0; //0. đang chơi game
                    //1. hết game
                    //2. người chơi chọn thoát

    while (!status && p.life) {
        
        board[curPosition.y][curPosition.x].isSelected = 1;

        renderBoard(board);

       

        move(board, curPosition, status, p, selectedPos, couple);

        if ((!checkValidPairs(board))) status = 1;
        
    }

    renderBoard(board);
    deleteBoard(board);
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
        if (c == 'y' || c == 'Y') easyMode(p);
        else writeLeaderBoard(p);
    }
    else if (p.life == 0) {
        displayStatus(0);
        writeLeaderBoard(p);
        Sleep(2000);
    }
    system("cls");
}

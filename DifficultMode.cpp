#include "DifficultMode.h"
#include <iostream>
using namespace std;

char BG[20][41];

void push(CELL_2*& head, CELL_2* p) {
    if (head == NULL) {
        head = p;
    }
    else {
        CELL_2* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = p;
    }
}

void initList(CELL_2** arr) {
    for (int i = 0; i < BOARDHEIGHT2; i++) {
        arr[i] = NULL;
        for (int j = 0; j < 8; j++) {
            CELL_2* p = new CELL_2;
            p->i = i;
            p->j = j;
            p->next = NULL;
            push(arr[i], p);
        }
    }

    int flagNum = 20;
    while (flagNum) {
        int i, time = 2;
        char c = 65 + rand() % 26;
        while (time)
        {
            i = rand() % 5;
            int j = rand() % 8;
            CELL_2* p = findTheNode(arr, i, j);
            if (p->c == ' ') {
                p->c = c;
                time--;
            }
        }
        flagNum--;
    }
}

void deleteList(CELL_2** arr) {
    for (int i = 0; i < BOARDHEIGHT2; i++) {
        CELL_2* temp;
        while (arr[i] != NULL)
        {
            temp = arr[i];
            arr[i] = arr[i]->next;
            temp->deleteBox();
            if (temp->j < 4) displayBackground(BG, temp->j, i);
            Sleep(500);
            delete temp;
        }
    }
    delete[]arr;
}

void renderList(CELL_2** arr) {
    for (int i = 0; i < BOARDHEIGHT2; i++) {
        CELL_2* temp = arr[i];
        while (temp != NULL)
        {
            temp->drawBox(112);
            temp = temp->next;
        }
    }
}

void move(CELL_2** arr, position& pos, int& status, player& p, position selectedPos[], int& couple) {
    int temp, key;
    temp = _getch();
    if (temp && temp != 224) { // neu ko phai la dau mui ten
        if (temp == ESC_KEY) { // neu la ESC
            status = 2;
        }
        else if (temp == ENTER_KEY) { // neu la Enter
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {
                CELL_2* temp = findTheNode(arr, pos.y, pos.x);
                temp->drawBox(70);
                Sleep(500);

                temp->isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                wrongSound();
                p.life--;
                goToXY(70, 0);
                cout << "Life: " << p.life;
            } // kiem tra lap lai
            else {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                findTheNode(arr, pos.y, pos.x)->isSelected = 1;
                couple--;

                if (couple == 0) { // neu da chon 1 cap
                    CELL_2* p1, * p2;
                    p1 = findTheNode(arr, selectedPos[0].y, selectedPos[0].x);
                    p2 = findTheNode(arr, selectedPos[1].y, selectedPos[1].x);
                    if (p1->c == p2->c) {  // neu cap nay hop nhau
                        if (allCheck(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x)) {
                            correctSound();
                            p.point += 20;
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            p1->drawBox(40);
                            p2->drawBox(40);
                            Sleep(500);

                            DifMode(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, BG);
                        }
                        else {
                            wrongSound();
                            p1->drawBox(70);
                            p2->drawBox(70);
                            Sleep(500);
    
                            p.life--;
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    }
                    else {
                        wrongSound();
                        p1->drawBox(70);
                        p2->drawBox(70);
                        Sleep(500);

                        p.life--;
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }
                    // tra ve noi san xuat
                    p1->isSelected = 0;
                    p2->isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < BOARDHEIGHT2; i++) {
                        for (int j = pos.x; j < BOARDWIDTH2; j++) {
                            if (findTheNode(arr, i, j) != NULL) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i <= pos.y; i++) { // chuyen den CELL_1 o tren
                        for (int j = 0; j <= pos.x; j++) {
                            if (findTheNode(arr, i, j) != NULL) {
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
            findTheNode(arr, pos.y, pos.x)->isSelected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < BOARDWIDTH2; i++) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH2; i++) {
                for (int j = BOARDHEIGHT2 - 1; j > pos.y; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) {
                for (int j = BOARDHEIGHT2 - 1; j > pos.y; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
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
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGHT2; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH2; i++) {
                for (int j = 0; j < pos.y; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = 0; j < pos.y; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
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
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT2; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH2 - 1; j > pos.x; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT2; i++) {
                for (int j = BOARDWIDTH2 - 1; j > pos.x; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
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
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT2; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH2; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = 0; j < pos.x; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT2; i++) {
                for (int j = 0; j < pos.x; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
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

void difficultMode(player& p) {
    srand(time(0));
    getBackground(BG);

    CELL_2** board = new CELL_2 * [BOARDHEIGHT2];
    initList(board);

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
        findTheNode(board, curPosition.y, curPosition.x)->isSelected = 1;

        renderList(board);

        move(board, curPosition, status, p, selectedPos, couple);

        if ((!checkValidPairs(board))) status = 1;
    }

    renderList(board);
    deleteList(board);
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
        if (c == 'y' || c == 'Y') difficultMode(p);
        else writeLeaderBoard(p);
    }
    else if (p.life == 0) {
        displayStatus(0);
        writeLeaderBoard(p);
        Sleep(500);
    }
    system("cls");
}
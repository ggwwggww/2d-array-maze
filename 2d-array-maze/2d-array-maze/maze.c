#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include <conio.h> 

struct user {
    int x;
    int y;
};

struct monster {
    int x;
    int y;
};

struct monster mon;
struct monster prev_mon;
struct user character;
struct user prev_character;

char field[6][8] = {
    "10111111",
    "10110101",
    "10000001",
    "10110101",
    "10100101",
    "11112111"
};

void starting_point();
void user_move();
void monster_move();
void output();
int escape();
int dead();

int main(void) {

    starting_point();

    while (1) {

        system("cls");


        prev_mon = mon;
        prev_character = character;


        user_move();

        monster_move();

        output();

        if (escape()) {
            printf("\nEsacape");
            break;
        }

        if (dead()) {
            printf("\nDead");
            break;
        }

        Sleep(16);
    }
    return 0;
}

void starting_point() {
    mon.x = 6;
    mon.y = 4;
    character.x = 1;
    character.y = 0;

}

void user_move() {
    if (_kbhit()) {

        char gps;
        gps = _getch();

        if (gps == 'd' && field[character.y][character.x + 1] != '1') {
            character.x += 1;
        }
        else if (gps == 'a' && field[character.y][character.x - 1] != '1') {
            character.x -= 1;
        }
        else if (gps == 'w' && field[character.y - 1][character.x] != '1') {
            character.y -= 1;
        }
        else if (gps == 's' && field[character.y + 1][character.x] != '1') {
            character.y += 1;
        }
    }

}

void monster_move() {

    srand((unsigned int)time(NULL));
    int mvx = rand() % 8;
    int mvy = rand() % 6;

    if (field[mvy][mvx] != '1' && field[mvy][mvx] != '2') {
        mon.x = mvx;
        mon.y = mvy;
    }
}
void output() {

    field[prev_character.y][prev_character.x] = '0';
    field[character.y][character.x] = 'P';

    field[prev_mon.y][prev_mon.x] = '0';
    field[mon.y][mon.x] = 'M';

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == character.y && j == character.x) {
                printf("P");
            }
            else {
                if (j == 0) { printf("\n"); }
                printf("%c", field[i][j]);
            }
        }
    }
}

int escape() {
    return character.y == 5 && character.x == 4;
}

int dead() {
    return field[character.y][character.x] == field[mon.y][mon.x];
}
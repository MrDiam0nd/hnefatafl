#pragma once
#include "raylib.h"

struct board{
    uint64_t pieces[3];
    uint8_t turn;
};

int min(int a,int b);
int max(int a,int b);
int getpiece(struct board b, int pos);
int setpiece(struct board* b, int pos, int piece);
void printBits(uint64_t bits);
void setbit(uint64_t* num, int pos);
void clearbit(uint64_t* num, int pos);
int collisionpointrect(int px,int py, int rx, int ry, int sx, int sy);
void loadboard(struct board *board);
void checkmove(struct board *board,int x, int y);

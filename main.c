#include "raylib.h"
#include <stdio.h>
#include <stdint.h>

#include "draw.h"
#include "main.h"

int main()
{
    int windowWidth = 800;
    int windowHeight = 450;
    InitWindow(windowWidth,windowHeight,"basic window");

    SetTargetFPS(30);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    struct board board;
    // printBits(board.pieces[0]);
    // printBits(board.pieces[1]);
    // printBits(board.pieces[2]);
    // printf("\n");
    
    /*
    setpiece(&board, 1+0*9,0x1);
    setpiece(&board, 2+0*9,0x2);
    setpiece(&board, 3+0*9,0x1);
    setpiece(&board, 4+0*9,0x2);
    printBits(board.pieces[0]);
    printBits(board.pieces[1]);
    printBits(board.pieces[2]);
    printf("\n");

    setpiece(&board, 0+1*9,0x1);
    setpiece(&board, 0+2*9,0x2);
    setpiece(&board, 0+3*9,0x1);
    setpiece(&board, 0+4*9,0x2);

    setpiece(&board, 8+8*9,0x3);

    printBits(board.pieces[0]);
    printBits(board.pieces[1]);
    printBits(board.pieces[2]);
    printf("\n");
    */

    /*
    for(int i = 0; i<81;i++){
	setpiece(&board,i,0x3&i);
    }

    printBits(board.pieces[0]);
    printBits(board.pieces[1]);
    printBits(board.pieces[2]);
    printf("\n");
    */

    while(!WindowShouldClose())
    {
	if(IsWindowResized())
	{
	    windowWidth = GetScreenWidth();
	    windowHeight = GetScreenHeight();
	}

	DrawBoard(windowWidth,windowHeight,board);
    }

    CloseWindow();

    return 0;
}

int min(int a,int b)
{
    if(a<b)
    {
	return a;
    }
    return b;
}

int getpiece(struct board b, int pos)
{
    if(pos < 32)
    {
	return ((b.pieces[0] >> (pos*2)) & 0x3);
    }else if(pos < 64)
    {
	return ((b.pieces[1] >> ((pos-32)*2)) & 0x3);
    }else if(pos < 96)
    {
	return ((b.pieces[2] >> ((pos-64)*2)) & 0x3);
    }
    return 0;
}

int setpiece(struct board* b, int pos, int piece)
{
    if(pos < 32)
    {
	if((piece & 0x1) == 1)
	{
	    setbit(&b->pieces[0],pos*2);
	}else
	{
	    clearbit(&b->pieces[0],pos*2);
	}

	if(((piece>>0x1) & 0x1) == 1)
	{
	    setbit(&b->pieces[0],pos*2+1);
	}else
	{
	    clearbit(&b->pieces[0],pos*2+1);
	}
    }else if(pos < 64)
    {
	if((piece & 0x1) == 1)
	{
	    setbit(&b->pieces[1],(pos-32)*2);
	}else
	{
	    clearbit(&b->pieces[1],(pos-32)*2);
	}

	if(((piece>>0x1) & 0x1) == 1)
	{
	    setbit(&b->pieces[1],(pos-32)*2+1);
	}else
	{
	    clearbit(&b->pieces[1],(pos-32)*2+1);
	}
    }else if(pos < 96)
    {
	if((piece & 0x1) == 1)
	{
	    setbit(&b->pieces[2],(pos-64)*2);
	}else
	{
	    clearbit(&b->pieces[2],(pos-64)*2);
	}

	if(((piece>>0x1) & 0x1) == 1)
	{
	    setbit(&b->pieces[2],(pos-64)*2+1);
	}else
	{
	    clearbit(&b->pieces[2],(pos-64)*2+1);
	}
    }
    return 0;
}

void printBits(uint64_t bits)
{
    for(int i = 0; i<64; i++)
    {
	printf("%d",((bits >> (63-i)) & 0x1));
    }
    printf("\n");
    return;
}

void setbit(uint64_t* num, int pos)
{
    *num = *num | ((uint64_t)0x1 << pos);
    return;
}

void clearbit(uint64_t* num, int pos)
{
    *num = *num & ~((uint64_t)0x1 << pos);
    return;
}

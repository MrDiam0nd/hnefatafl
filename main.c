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

    int mousex;
    int mousey;

    loadboard(&board);

    while(!WindowShouldClose())
    {
	    if(IsWindowResized())
	    {
	        windowWidth = GetScreenWidth();
	        windowHeight = GetScreenHeight();
	    }

	    DrawBoard(windowWidth,windowHeight,&board);
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

int max(int a,int b)
{
    if(a>b)
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

int collisionpointrect(int px,int py, int rx, int ry, int sx, int sy)
{
    if((px>=rx) && (px<=(rx+sx)) && (py>=ry) && (py<=(ry+sy)))
    {
	return 1;
    }
    return 0;
}

void loadboard(struct board *board)
{
    for(int i = 0; i< 81; i++)
    {
	if((i==3)||(i==4)||(i==5)||(i==4+1*9) || (i==0+3*9)||(i==0+4*9)||(i==0+5*9)||(i==1+4*9) || (i==8+3*9)||(i==8+4*9)||(i==8+5*9)||(i==7+4*9) || (i==3+8*9)||(i==4+8*9)||(i==5+8*9)||(i==4+7*9))
	{
	    setpiece(board, i,0x1);
	}else if((i==4+2*9)||(i==4+3*9) || (i==2+4*9)||(i==3+4*9) || (i==5+4*9)||(i==6+4*9) || (i==4+5*9)||(i==4+6*9))
	{
	    setpiece(board, i,0x2);
	}else if(i==4+4*9)
	{
	    setpiece(board,i,0x3);
	}else
	{
	    setpiece(board, i,0x0);
	}
    }

    board->turn = 0;
}

void checkmove(struct board *board,int x, int y)
{
    int piece = getpiece(*board,x+y*9);
    if(piece == 0x3){
        piece = 0x2;
    }

    int a = -1;
    int b = -1;
    int c = -1;
    int d = -1;

    if(x+2 < 9)
    {
        a = x+2+y*9;
        b = x+1+y*9;
        if(y+1<9)
        {
            c = x+(y+1)*9;
        }
        if(y-1>=0)
        {
            d = x+(y-1)*9;
        }

        if((getpiece(*board,x+2+y*9) == piece) || (piece == 0x2 && getpiece(*board,x+2+y*9) == 0x3) || (x+2+y*9==4+4*9) || (x+2+y*9==0+0*9) ||(x+2+y*9==0+8*9) ||(x+2+y*9==8+0*9) ||(x+2+y*9==8+8*9))
        {
            if(getpiece(*board,x+1+y*9) == (piece ^ 0x3))
            {
                setpiece(board,x+1+y*9,0);
            }
            if(getpiece(*board,x+1+y*9) == 0x3 && piece == 0x1)
            {
                int kill = 1;
                if(y+1<9)
                {
                    if(getpiece(*board,x+1+(y+1)*9) != 0x1 && !(x+1+(y+1)*9==4+4*9) && !(x+1+(y+1)*9==0+0*9) && !(x+1+(y+1)*9==0+8*9) && !(x+1+(y+1)*9==8+0*9) && !(x+1+(y+1)*9==8+8*9))
                    {
                        kill = 0;
                    }
                }
                if(y-1>=0)
                {
                    if(getpiece(*board,x+1+(y-1)*9) != 0x1 && !(x+1+(y-1)*9==4+4*9) && !(x+1+(y-1)*9==0+0*9) && !(x+1+(y-1)*9==0+8*9) && !(x+1+(y-1)*9==8+0*9) && !(x+1+(y-1)*9==8+8*9))
                    {
                        kill = 0;
                    }
                }
                setpiece(board,x+1+y*9,0);
            }
        }
    }
    if(y+2 < 9)
    {

    }
    if(x-2 >= 0)
    {

    }
    if(y-2 >= 0)
    {

    }
}
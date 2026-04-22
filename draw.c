#include "raylib.h"
#include <stdio.h>
#include <stdint.h>

#include "main.h"
#include "draw.h"

Color background = {76,92,45,255};

Color wood = {132,36,12,255};
Color borders = {60,50,50,255};
Color darkSquares = {66,18,6,255};

int edgedist = 10;
float bordersize = 1.0f/32.0f;
float gapsize = 1.0f/64.0f;

int chosenx = -1;
int choseny = -1;

void DrawBoard(int width, int height, struct board *board)
{
    BeginDrawing();
    ClearBackground(background);

    int size = min(width, height);

    int posx = (width - size)/2 + edgedist;
    int posy = (height - size)/2 + edgedist;

    size -= 2*edgedist;

    DrawRectangle(posx,posy,size,size,wood);
    float edgeGap = size * bordersize;
    DrawRectangle(posx + edgeGap,posy + edgeGap,size - edgeGap * 2,size - edgeGap * 2,borders);

    float squareGap = size * gapsize;
    float squareDist = (size-2*edgeGap-squareGap)/9;
    float squareSize = (size-2*edgeGap-squareGap)/9 - squareGap;
    Color squareColor = wood;

    if(IsMouseButtonDown(1))
    {
	chosenx = -1;
	choseny = -1;
    }

    for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++)
	{
	    if((i==0&&j==0) || (i==4&&j==4) || (i==0&&j==8) || (i==8&&j==0) || (i==8&&j==8))
	    {
		squareColor = darkSquares;
	    }
	    DrawRectangle(posx+edgeGap+squareGap + squareDist * i, posy+edgeGap+squareGap + squareDist * j, squareSize, squareSize, squareColor);
	    squareColor = wood;

	    switch (getpiece(*board,i+j*9))
	    {
		case 0x1:
		    DrawCircle(posx+edgeGap+squareGap + squareDist * i + squareSize/2, posy+edgeGap+squareGap + squareDist * j + squareSize/2,squareSize/3,BLACK);
		    break;
		case 0x2:
		    DrawCircle(posx+edgeGap+squareGap + squareDist * i + squareSize/2, posy+edgeGap+squareGap + squareDist * j + squareSize/2,squareSize/3,WHITE);
		    break;
		case 0x3:
		    DrawCircle(posx+edgeGap+squareGap + squareDist * i + squareSize/2, posy+edgeGap+squareGap + squareDist * j + squareSize/2,squareSize/3,PURPLE);
		    break;
	    }

	    // check if hovered
	    if(collisionpointrect(GetMouseX(),GetMouseY(),posx+edgeGap+squareGap + squareDist * i, posy+edgeGap+squareGap + squareDist * j, squareSize, squareSize) == 1)
	    {
		DrawRectangle(posx+edgeGap+squareGap + squareDist * i, posy+edgeGap+squareGap + squareDist * j, squareSize, squareSize, (Color){0,0,0,60});
		if(IsMouseButtonPressed(0))
		{
		    if(chosenx != -1 && choseny != -1)
		    {
				if(i == chosenx || j ==  choseny)
				{
					int notblocked = 1;
					for(int k = 0; k<9; k++)
					{
						for(int l = 0; l<9; l++)
						{
							if(k >= min(i,chosenx) && k <= max(i,chosenx) && l >= min(j,choseny) && l <= max(j,choseny))
							{
								if((getpiece(*board,k+l*9) != 0) && !(k == chosenx && l == choseny) && !(k == i && l == j))
								{
									notblocked = 0;
								}
							}
						}
					}
					if(notblocked == 1)
					{
				
			int piece = getpiece(*board,chosenx+choseny*9);
			if(piece == 0x1 && getpiece(*board,i+j*9) == 0 && board->turn == 0)
			{
			    setpiece(board,chosenx+choseny*9,0x0);
			    setpiece(board,i+j*9,piece);
				board->turn = 1;
			}
			if((piece == 0x2 || piece == 0x3)&& getpiece(*board,i+j*9) == 0 && board->turn == 1)
			{
			    setpiece(board,chosenx+choseny*9,0x0);
			    setpiece(board,i+j*9,piece);
				board->turn = 0;
			} 
				}
		    }}
		    chosenx = i;
		    choseny = j;
		}
	    }

	    if((i==chosenx) && (j==choseny))
	    {
		DrawRectangle(posx+edgeGap+squareGap + squareDist * i, posy+edgeGap+squareGap + squareDist * j, squareSize, squareSize, (Color){228,174,197,60});
	    }
	}
    }

    EndDrawing();
    return;
}

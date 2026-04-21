#include "raylib.h"
#include <stdio.h>
#include <stdint.h>

#include "main.h"

Color background = {76,92,45,255};

Color wood = {132,36,12,255};
Color borders = {60,50,50,255};
Color darkSquares = {66,18,6,255};

void DrawBoard(int width, int height, struct board board)
{
    BeginDrawing();
    ClearBackground(background);

    int size = min(width, height);

    int posx = (width - size)/2 + 10;
    int posy = (height - size)/2 + 10;

    size -= 20;

    DrawRectangle(posx,posy,size,size,wood);
    float edgeGap = size/32;
    DrawRectangle(posx + edgeGap,posy + edgeGap,size - edgeGap * 2,size - edgeGap * 2,borders);

    float squareGap = size/128;
    float squareDist = (size-2*edgeGap-2*squareGap)/9;
    float squareSize = (size-2*edgeGap-2*squareGap)/9 - 2*squareGap;
    Color squareColor = wood;

    for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++)
	{
	    if((i==0&&j==0) || (i==4&&j==4) || (i==0&&j==8) || (i==8&&j==0) || (i==8&&j==8))
	    {
		squareColor = darkSquares;
	    }
	    DrawRectangle(posx+edgeGap+squareGap*2 + squareDist * i, posy+edgeGap+squareGap*2 + squareDist * j, squareSize, squareSize, squareColor);
	    squareColor = wood;

	    switch (getpiece(board,i+j*9))
	    {
		case 0x1:
		    DrawCircle(posx+edgeGap+squareGap*2 + squareDist * i + squareSize/2, posy+edgeGap+squareGap*2 + squareDist * j + squareSize/2,squareSize/3,BLACK);
		    break;
		case 0x2:
		    DrawCircle(posx+edgeGap+squareGap*2 + squareDist * i + squareSize/2, posy+edgeGap+squareGap*2 + squareDist * j + squareSize/2,squareSize/3,WHITE);
		    break;
		case 0x3:
		    DrawCircle(posx+edgeGap+squareGap*2 + squareDist * i + squareSize/2, posy+edgeGap+squareGap*2 + squareDist * j + squareSize/2,squareSize/3,PURPLE);
		    break;
	    }
	}
    }

    EndDrawing();
    return;
}

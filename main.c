#include "raylib.h"
#include <stdio.h>

int min(int a,int b)
{
    if(a<b)
    {
	return a;
    }
    return b;
}

void DrawBoard(int width, int height)
{
    int size = min(width, height);

    int posx = (width - size)/2;
    int posy = (height - size)/2;

    DrawRectangle(posx,posy,size,size,BLUE);

    return;
}


int main()
{
    int windowWidth = 800;
    int windowHeight = 450;
    InitWindow(windowWidth,windowHeight,"basic window");

    SetTargetFPS(30);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while(!WindowShouldClose())
    {
	if(IsWindowResized())
	{
	    windowWidth = GetScreenWidth();
	    windowHeight = GetScreenHeight();
	}

	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawBoard(windowWidth,windowHeight);
	EndDrawing();
    }

    CloseWindow();

    return 0;
}

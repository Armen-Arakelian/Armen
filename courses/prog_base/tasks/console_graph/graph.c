#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

void draw()
{
    char push;
    int i, x, y, gX, gY, border, x1,y1;
    int green = BACKGROUND_GREEN;
    int blue = BACKGROUND_BLUE;
    int white = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
    int black = NULL;
    COORD pos;
    pos.X = 0;
    pos.Y = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("F(x) = 1.3*(x + 1) - 2\n");
    printf("F(x) = 1.5 * cos(0.2 * x)\n");
    border = 30;
    x = 50;
    y = 50;
    gX = 1;
    gY = 1;
    for(;;)
    {
        SetConsoleTextAttribute(hConsole, white);
        pos.X = x;
        pos.Y = y;
    for (i=y-border;i<y+border;i++)
    {
        pos.Y = i;
        SetConsoleCursorPosition(hConsole, pos);
        puts("|");
    }
      for (i=y-border;i<y+border;i+=gY)
    {
        pos.Y = i;
        SetConsoleCursorPosition(hConsole, pos);
        puts("+");
    }
    pos.Y = y;
    for (i=x-border;i<x+border;i++)
    {
        pos.X = i;
        SetConsoleCursorPosition(hConsole, pos);
        puts("-");
    }
      for (i=x-border;i< x+border;i+=gX)
    {
        pos.X = i;
        SetConsoleCursorPosition(hConsole, pos);
        puts("+");
    }
    for (i=x-border;i<border+x;i++)
    {
        pos.X = i;
        pos.Y = y+gY*(1.5 * cos(0.2 * (pos.X)))/gX;
        if (pos.Y >= border+y) break;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, blue);
        puts(" ");
    }
     for (i=x-border;i<border+x;i++)
    {
        pos.X = i;
        pos.Y = y+ gY*(1.3*(pos.X + 1) - 2)/gX;
        if (pos.Y >= border+y) break;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, green);
        puts(" ");
    }
    SetConsoleTextAttribute(hConsole, black);
    x1 = pos.X;
    y1 = pos.Y;
    pos.X = 0;
    pos.Y = 0;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, white);
    printf("F(x) = 1.3*(x + 1) - 2\n");
    printf("F(x) = 1.5 * cos(0.2 * x)\n");
    printf("Push 1 to make scale of X bigger\n");
    printf("Push 2 to make scale of Y bigger\n");
    printf("Push 3 to make scale of X smaller\n");
    printf("Push 4 to make scale of Y smaller\n");
    printf("Push 5 to replace centre right\n");
    printf("Push 6 to replace centre up\n");
    printf("Push 7 to replace centre left\n");
    printf("Push 8 to replace centre down\n");
    pos.X =x1;
    pos.Y =y1;
    SetConsoleCursorPosition(hConsole, pos);
    push = getch();
    switch(push)
    {
    case '1':
        if (gX == 10)
            break;
        gX++;
        break;
    case '2':
         if (gY == 10)
            break;
        gY++;
        break;
    case '3':
         if (gX == 1)
            break;
        gX--;
        break;
    case '4':
        if (gY == 1)
            break;
        gY--;
        break;
    case '5':
        if (x == 70)
            break;
        x+=gX;
        break;
    case '6':
        if (y == 70)
            break;
        y+=gY;
        break;
    case '7':
        if (x == border)
            break;
        x-=gX;
        break;
    case '8':
        if (y == border)
            break;
        y-=gY;
        break;
         }
         system("cls");
    }
}

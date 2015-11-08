#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void putAst(COORD pos)
{
  int i, color = 0;
  int aqua = BACKGROUND_BLUE | BACKGROUND_GREEN;
  int blue = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
  int green = BACKGROUND_GREEN;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hConsole, blue);
  puts("*");
    while (pos.X < 79 || pos.Y<24)
    {
    if (pos.X<79)
    pos.X++;
    else if (pos.Y >= 24) break;
    else pos.Y++;
     while (pos.X && pos.Y<24)
    {
        SetConsoleCursorPosition(hConsole, pos);
        puts("*");
        switch (color % 3)
        {
        case 0 :
            SetConsoleTextAttribute(hConsole, aqua);
            break;
        case 1:
            SetConsoleTextAttribute(hConsole, green);
            break;
        case 2:
            SetConsoleTextAttribute(hConsole, blue);
            break;
        }
        Sleep(1);
        pos.X--;
        pos.Y++;
        if (pos.X >=79 && pos.Y>=24) return ;
        SetConsoleCursorPosition(hConsole, pos);
        puts("*");
        Sleep(1);
    }
    color++;
    if (pos.Y<24)
    pos.Y++;
    else if (pos.X>=79) break;
    else pos.X++;
    while (pos.Y && pos.X< 79)
    {
        SetConsoleCursorPosition(hConsole, pos);
        puts("*");
        switch (color % 3)
        {
        case 0 :
            SetConsoleTextAttribute(hConsole, aqua);
            break;
        case 1:
            SetConsoleTextAttribute(hConsole, green);
            break;
        case 2:
            SetConsoleTextAttribute(hConsole, blue);
            break;
        }
        Sleep(1);
        pos.X++;
        pos.Y--;
        if (pos.X >=79 && pos.Y>=24) return ;
        SetConsoleCursorPosition(hConsole, pos);
        puts("*");
        Sleep(1);
    }
    color++;
    }
    SetConsoleCursorPosition(hConsole, pos);
     SetConsoleTextAttribute(hConsole, green);
    puts("*");
}

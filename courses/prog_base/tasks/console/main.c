#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = 0;
    putAst(pos);
    return EXIT_SUCCESS;
}

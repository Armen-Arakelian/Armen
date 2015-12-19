#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_PLAYERS 10
#define MAX_LENGTH 60

const int wBorder = 20;
const int hBorder = 5;
enum direct {UP = 1, DOWN, LEFT, RIGHT} curDirect = RIGHT;


typedef struct Coord
{
    int x, y
} Coord;

typedef struct Player
{
    char name[50];
    int score;
} Player;

int update(Coord snake[MAX_LENGTH], Coord head, Coord tail, int * score, int snakeSize, int lvl)
{
    int lvlPause;
   head.x = snake[0].x = 10;
   head.y = snake[0].y = 12;
   tail.x = snake[1].x = 10;
   tail.y = snake[1].y = 12;
   printFrame(10, 3, 70, 22);
   printSnake(snake, snakeSize);
   int isEaten = foodSpawn();
   switch(lvl)
        {
        case 1:
            lvlPause = 200;
            break;
        case 2 :
            lvlPause = 150;
            break;
        case 3:
            lvlPause = 130;
            break;
        case 4:
            lvlPause = 110;
            break;
        case 5:
            lvlPause = 90;
            break;
        case 6:
            lvlPause = 80;
            break;
        case 7:
            lvlPause = 70;
            break;
        case 8:
            lvlPause = 60;
            break;
        case 9:
            lvlPause = 50;
            break;

        }
    while (1)
    {
        for (int i=snakeSize;i>0;i--)
            {
                snake[i].y = snake[i-1].y;
                snake[i].x = snake[i-1].x;
            }
        switch(curDirect)
        {
        case UP:
            snake[0].y--;
            head.y--;
            break;
        case DOWN:
            snake[0].y++;
            head.y++;
            break;
        case LEFT:
            snake[0].x--;
            head.x--;
            break;
        case RIGHT:
            snake[0].x++;
            head.x++;
        }
        if (crashCheck(snakeSize, snake, &head))
            return 0;
        reprintSnake(snake, &head, &tail);
        tail.x = snake[snakeSize-1].x;
        tail.y = snake[snakeSize-1].y;
        if (head.x == isEaten/1000-wBorder && head.y == isEaten%1000-hBorder)
        {
            isEaten = foodSpawn(snake, snakeSize);
            snakeFeed(snake, &tail, &snakeSize);
            (*score)++;
        }
        Sleep(lvlPause);
    }
    return 0;
}

void printSnake(Coord snake[MAX_LENGTH], int snakeSize)
{
    int i;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
    for (i=0; i<snakeSize;i++)
    {
        putCursor(snake[i].x+wBorder, snake[i].y+hBorder);
        puts(" ");
    }
    SetConsoleTextAttribute(hConsole, NULL);
}

void reprintSnake(Coord snake[MAX_LENGTH], Coord *head, Coord *tail)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE|BACKGROUND_GREEN);
    putCursor(tail->x + wBorder, tail->y + hBorder);
    puts(" ");
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN|BACKGROUND_RED);
    putCursor(head->x+wBorder, head->y+hBorder);
    puts(" ");
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE);
    putCursor(snake[1].x+wBorder, snake[1].y+hBorder);
    puts(" ");
    SetConsoleTextAttribute(hConsole, NULL);
}


void putCursor(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}

void readBut()
{
    char c;
    while (1)
    {
        c = getch();
        switch(c)
        {
        case 'w':
            if (curDirect != DOWN)
                curDirect = UP;
            break;
        case 's':
            if ( curDirect != UP)
                curDirect = DOWN;
            break;
        case 'a':
            if (curDirect != RIGHT)
                curDirect = LEFT;
            break;
        case 'd':
            if (curDirect != LEFT)
            curDirect = RIGHT;
            break;
            default:
            break;
    }
    }
}

int foodSpawn(Coord snake[MAX_LENGTH], int snakeSize)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color[6];
    color[0] = FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN;
    color[1] = FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN;
    color[2] = FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN;
    color[3] = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN;
    color[4] = FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN;
    color[5] = FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN;
    int x ;
    int y ;
    x = rand()%15 + wBorder;
    y = rand()%15 + hBorder;
    if (foodCheck(snake, x, y, snakeSize))
            return foodSpawn(snake, snakeSize);
    putCursor(x, y);
    SetConsoleTextAttribute(hConsole, color[rand()%5]);
    puts("@");
    SetConsoleTextAttribute(hConsole, NULL);
    return 1000*x+y;
}

void snakeFeed(Coord snake[MAX_LENGTH], Coord *tail, int * snakeSize)
{
    (*snakeSize)++;
    if (!(snake[*snakeSize-3].x - snake[*snakeSize-2].x))
    {
        if ((snake[*snakeSize-3].y - snake[*snakeSize-2].y) == -1)
        {
            snake[*snakeSize-1].y = snake[*snakeSize-2].y+1;
            tail->y++;
            snake[*snakeSize-1].x = snake[*snakeSize-2].x;
        }
        if ((snake[*snakeSize-3].y - snake[*snakeSize-2].y) == 1)
        {
            snake[*snakeSize-1].y = snake[*snakeSize-2].y-1;
            tail->y--;
            snake[*snakeSize-1].x = snake[*snakeSize-2].x;
        }
    }
    if (!(snake[*snakeSize-3].y-snake[*snakeSize-2].y))
    {
        if ((snake[*snakeSize-3].x - snake[*snakeSize-2].x) == -1)
        {
            snake[*snakeSize-1].x = snake[*snakeSize-2].x+1;
            tail->x++;
            snake[*snakeSize-1].y = snake[*snakeSize-2].y;
        }
        if ((snake[*snakeSize-3].x - snake[*snakeSize-2].x) == 1)
        {
            snake[*snakeSize-1].x = snake[*snakeSize-2].x-1;
            tail->x--;
            snake[*snakeSize-1].y = snake[*snakeSize-2].y;
        }
    }
}
int crashCheck(int snakeSize, Coord snake[snakeSize], Coord *head)
{
    int i;
    if ( head->x == 9 -wBorder || head->x == 70 - wBorder || head->y == 2 - hBorder|| head->y == 22 -hBorder)
        return 1;
    for (i=2; i<snakeSize;i++)
    {
        if ((head->x == snake[i].x && head->y == snake[i].y))
            return 1;
    }
    return 0;
}

int foodCheck(Coord snake[MAX_LENGTH], int x, int y, int snakeSize)
{
    int i;
    for (i=0;i<snakeSize;i++)
    {
        if (snake[i].x + wBorder == x && snake[i].y +hBorder== y)
            return 1;
    }
    return 0;
}

void printFrame(int xB, int yB, int xE, int yE)
{
    int aqua = BACKGROUND_BLUE|BACKGROUND_GREEN;
    int blue = FOREGROUND_BLUE;
    int white = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
    int black = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    SetConsoleTextAttribute(hConsole, aqua);
     for(pos.Y=yB;pos.Y<yE;pos.Y++)
    {
       for(pos.X=xB;pos.X<xE;pos.X++)
       {
           SetConsoleCursorPosition(hConsole, pos);
           putchar(' ');
       }
   }
   SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
    for(pos.Y=yB-1;pos.Y<=yE;pos.Y++)
    {
        pos.X = xB - 1;
        SetConsoleCursorPosition(hConsole, pos);
        putchar('|');
        pos.X = xE;
        SetConsoleCursorPosition(hConsole, pos);
        putchar('|');
    }
    for(pos.X=xB-1;pos.X<=xE;pos.X++)
 {
        pos.Y = yB - 1;
        SetConsoleCursorPosition(hConsole, pos);
        putchar('-');
        pos.Y = yE;
        SetConsoleCursorPosition(hConsole, pos);
        putchar('-');
    }
    SetConsoleTextAttribute(hConsole, black);
    SetConsoleTextAttribute(hConsole, white);
   }

void addPlayer(Player players[MAX_PLAYERS])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = MAX_PLAYERS-1; i>=0;i--)
    {
        players[i] = players[i-1];
    }
    printFrame(20, 10,60,20);
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE|BACKGROUND_GREEN);
    putCursor(27, 12);
    printf("Welcome to Console snake!");
    putCursor(30, 17);
    puts("Enter your nickname");
    putCursor(30, 18);
    gets(players[0].name);
    players[0].score = 0;
    SetConsoleTextAttribute(hConsole, NULL);
}

void leaderboard(Player players[MAX_PLAYERS])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printFrame(25, 1, 55, 24);
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE|BACKGROUND_GREEN);
    putCursor(34, 1);
    printf("Leaderboard");
    putCursor(27, 3);
    printf("Nickname");
    putCursor(46, 3);
    printf("Score");
    for (int i = 0;i<MAX_PLAYERS;i++)
    {
        putCursor(26, 5+2*i);
        printf("%s", players[i].name);
        putCursor(45, 5+2*i);
        printf("%d", players[i].score);
    }
    SetConsoleTextAttribute(hConsole, NULL);
}

void save(Player players[MAX_PLAYERS], char * filename)
{
    FILE * fp;
    int i;
    if ((fp = fopen(filename, "wb")) == NULL)
        exit(EXIT_FAILURE);
    for (i=0;i<MAX_PLAYERS;i++)
    {
        fwrite((players+i), sizeof(Player), 1, fp);
    }
    fclose(fp);
}

void deserialization(Player players[MAX_PLAYERS],char * filename)
{
     FILE * fp;
    int i;
    if ((fp = fopen(filename, "rb")) == NULL)
        fclose(fp);
    for (i=0;i<MAX_PLAYERS;i++)
    {
        fread((players+i), sizeof(Player), 1, fp);
    }
    fclose(fp);
}

int main()
{
    int snakeSize = 2;
    int lvl;
    char * filename = "leaderboard.bin";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Player players[MAX_PLAYERS];
    Coord snake[MAX_LENGTH];
    Coord head;
    Coord tail;
    for (int i = 0;i<MAX_PLAYERS;i++)
    {
        strcpy(players[i].name, "player");
        players[i].score = 0;
    }
    deserialization(players, filename);
    addPlayer(players);
    system("cls");
    leaderboard(players);
    getch();
    system("cls");
    int score = 0;
    printFrame(20, 10,75,20);
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE|BACKGROUND_GREEN);
    putCursor(21, 12);
    printf("Press 'w', 'a', 's', 'd' to control snake");
    putCursor(21, 14);
    printf("Enter number of level you want to play (from 1 to 9)");
    putCursor(27, 15);
    lvl = inputCheck(lvl);
    SetConsoleTextAttribute(hConsole, NULL);
    system("cls");
    HANDLE but = CreateThread(NULL, 0, readBut, NULL,0, NULL);
    update(snake, head, tail, &score, snakeSize, lvl);
    players[0].score = score;
    system("cls");
    printFrame(25, 10, 55, 15);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN);
    putCursor(35, 12);
    puts("CAME OVER");
    save(players, filename);
    getch();
    system("cls");
    return 0;
    }

int inputCheck(int lvl)
{
    scanf("%d", &lvl);
    if (lvl<1 || lvl > 9)
    {
        putCursor(27, 15);
        printf("Invalid input, try again");
        return inputCheck(lvl);
    }
    return lvl;
}






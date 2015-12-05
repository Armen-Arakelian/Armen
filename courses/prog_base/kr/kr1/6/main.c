#include <stdio.h>
#include <stdlib.h>

typedef struct Point
    {
        int x,y
    } Point;

int main()
{
    Point A;
    Point B;
    Point C;
    printf("Enter coordinates of points A(x,y), B(x,y), C(x,y)\n");
    scanf("%d", &A.x);
    scanf("%d", &A.y);
    scanf("%d", &B.x);
    scanf("%d", &B.y);
    scanf("%d", &C.x);
    scanf("%d", &C.y);
    distance(A, B, C);
    return 0;
}

void distance(Point A, Point B, Point C )
{
    char p1;
    char p2;
    double distance[3];
    double min;
    distance[0] = sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
    distance[1] = sqrt(pow((C.x - A.x), 2) + pow((C.y - A.y), 2));
    distance[2] = sqrt(pow((B.x - C.x), 2) + pow((B.y - C.y), 2));
    printf("Distance AB : %f\nDistance AC : %f\nDistance BC : %f", distance[0], distance[1], distance[2]);
    puts("\n");
    min = distance[0];
    p1 = 'A';
    p2 = 'B';
    if (distance[1]< min)
    {
        min = distance[1];
        p1 = 'A';
        p2 = 'C';
    }
    if (distance[2]< min)
    {
        min = distance[2];
        p1 = 'B';
        p2 = 'C';
    }
    printf("Distance %c%c ", p1, p2);
    puts("");
    printf("%f", min);
}





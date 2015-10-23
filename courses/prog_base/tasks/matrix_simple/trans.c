#include <stdio.h>
#include <stdlib.h>

void fillRand (int mat[4][4])
{
    int i,j,n = 4;
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            mat[i][j] = rand()%1998 - 999;
        }
    }

}

void rotateCW180(int mat[4][4])
{
    int i,j,n = 4;
    int mat1 [4][4];
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            mat1[i][j] = mat[i][3-j];
        }
    }

      for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            mat[i][j] = mat1[3-i][j] ;
        }
    }
}


void flipH(int mat[4][4])
{
    int i,j,n = 4;
    int mat1 [4][4];
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
           mat1[i][j] = mat[i][3-j];
        }
    }

      for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
           mat[i][j] = mat1[i][j];
        }
    }
}

void transposSide(int mat[4][4])
{
     int i,j,n = 4;
    int mat1 [4][4];
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
           mat1[i][j] = mat[j][i];
        }
    }

      for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
           mat[i][j] = mat1[3-i][3-j];
        }
    }
}






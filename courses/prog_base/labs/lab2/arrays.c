#include <stdio.h>
#include <stdlib.h>

void fillRand2(int arr[], int size)
{
    int a, b,i;
    for (i=0; i<size; i++)
    {
    arr[i] = rand() % 511 - 255;
    }
}
int checkRand2(int arr[], int size)
{
    int i;
    for (i = 0; i<size; i++)
    {
        if (arr[i]>=-255 && arr[i]<=255) return 1;
        else
            return 0;
    }
}

float meanValue(int arr[], int size)
{
    int i, s = 0;
    for (i = 0; i<size; i++)
    {
        s += arr[i];
    }
    return s/size;
}

int minValue(int arr[], int size)
{
    int i, min = arr[0];
    for (i = 1; i<size; i++)
    {
        if (arr[i]<min) min = arr[i];
    }
    return min;
}

int meanIndex(int arr[], int size)
{
    int i, j =0;
    float s,c =0;
    for (i = 0; i<size; i++)
    {
        c += arr[i];
    }
    c =c/size;
    s = abs(c - arr[0]);
    for (i=1; i<size ;i++)
    {
        if (abs(c - arr[i]) < s) j = i;
    }
    return j;
}

int minIndex(int arr[], int size)
{
    int i, min = arr[0], j =0;
    for (i=1; i<size; i++)
    {
        if (arr[i] < min) j = i;
    }
    return j;
}

int maxOccurance(int arr[], int size)
{
    int i, max = arr[0], g = 0, j, n;
    for(i = 0; i< size ;i++)
    {
        n = 0;
        for(j=i + 1;j<size;j++)
        {
            if (arr[i] == arr[j]) n++;
        }
        if ((g < n) || (g == n && max < arr[i]))
        {
            g = n;
            max = arr[i];
        }
    }
    return max;
}

void sub(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for (i = 0; i<size; i++)
    {
        res[i] = arr1[i] - arr2[i];
    }
}

int lt(int arr1[], int arr2[], int size)
{
    int i, check =0;
    for (i=0; i< size; i++)
    {
        if (arr1[i] >= arr2[i]) check++;
    }
        if (!check) return 1;
        else
            return 0;
}

void land(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for (i=0;i<size; i++)
    {
        if (arr1[i] && arr2[i]) res[i] = 1;
        else
            res[i] = 0;
    }
}


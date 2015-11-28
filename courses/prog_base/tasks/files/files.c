#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void fprocess(const char * pread, const char * pwrite)
{
    FILE * fr;
    FILE * fw;
    char  str[100];
    char * str1;
    if((fr = fopen(pread, "r")) == NULL)
    {
        printf("Error opening file : %s \n", pread);
        exit(EXIT_FAILURE);
    }
    if(fw = freopen(pwrite, "w", stdout) == NULL)
    {
        printf("Error opening file : %s \n", pwrite);
        exit(EXIT_FAILURE);
    }
    fgets(str, sizeof(str), fr);
    str1 = strtok(str, " ");
    printf(str1);
    do
    {
        str1 = strtok('\0', " ");
        if(str1) printf("\n%s", str1);
    }
    while(str1);
    fclose(fr);
    fclose(fw);
}

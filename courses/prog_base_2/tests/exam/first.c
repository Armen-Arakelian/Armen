#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int getCountStr(char * fullStr, char * str)
{
    char * helpStr;
    int count = 0;
    helpStr = strstr(fullStr, str);
    printf("%s\n", helpStr);
    while(helpStr != NULL)
        {
            count++;
            printf("%s\n", helpStr);
            helpStr = strstr((helpStr + strlen(str)), str);
        }
    return count;
}


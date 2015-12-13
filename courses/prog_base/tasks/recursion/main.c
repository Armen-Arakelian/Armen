#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int count = 0;
    char str[100];
    scanf("%s", str);
    if (recurt(str, count) > 5)
        return 1;
    return 0;
}

int recurt(char * str, int count)
{
    if (*str == '\0')
        return count;
    if (isdigit(*str))
            count++;
    str++;
    return count = recurt(str, count);
}



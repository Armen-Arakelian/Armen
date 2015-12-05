#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str1[100];
    char str2[100];
    char max, min;
    scanf("%s", str1);
    scanf("%s", str2);
    if (!strcmp(str1, str2))
        {
            printf("Strings are not different");
            return 0;
        }
        else
        {
            for (int i = 0;i<strlen(str1);i++)
            {
                if (!isalpha(str1[i] && !isalpha(str2[i])))
                {
                    if(str1[i]<str2[i])
                    {
                        max = str2[i];
                        min = str1[i];
                    }
                    else
                    {
                        max = str1[i];
                        min = str2[i];
                    }
                    if (max - min != 32)
                    {
                        printf("Strings are different");
                        return 1;
                    }
                         printf("Strings are not different");
                         return 0;
                }
            }
        }
}

#include<stdio.h>
#include <string.h>

typedef struct
{
    char name[100];
    int mark;
} Student;

char * getName(char * buf)
{
    Student st;
    int checkMark = 0;
    char * result;
    buf = strtok(buf, "\n");
    do
    {
        sscanf(buf, "%s%d", st.name, &st.mark);
        if (st.mark > checkMark)
        {
            checkMark = st.mark;
            strcpy(result, st.name);
        }
        buf = strtok('\0', "\n");
    }
    while(buf);
    return result;
}

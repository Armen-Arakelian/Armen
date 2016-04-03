#include<stdio.h>
#include <string.h>

typedef struct
{
    char name[100];
    int mark;
} Student;

void getName(char * buf, char * result)
{
    Student st;
    int checkMark = 0;
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
}

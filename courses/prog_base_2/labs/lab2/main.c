#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "queue.h"

typedef int (*cmp_f)(queue_t * q);
typedef int (*react_f)(queue_t * q);

typedef struct dynamic_s {
    HANDLE hLib;
    cmp_f cmp;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

const char * userChoice();
void printQueue(queue_t * q, int sum);

int main(void) {
    const int MAX_QUEUE_SIZE = 15;
    queue_t * q = queue_new();
    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    int sum = 0;
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->cmp) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!");
    srand(time(NULL));
    while (queue_getSize(q) < MAX_QUEUE_SIZE) {
        queue_enqueue(q, rand() % 100);
        if(dll->cmp(q)) {
            sum = dll->react(q);
        }
        printQueue(q, sum);
    }
    queue_free(q);
    return 0;
}

const char * userChoice() {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        printf("Choose DLL to load:\n1. Lab2DLL1\n2. Lab2DLL2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "Lab2DLL1.dll";
        } else if (dllNum == 2) {
            return "Lab2DLL2.dll";
        }
    }
    return NULL;
}

void printQueue(queue_t * q, int sum)
{
    system("cls");
    printf("Queue: \n");
    queue_print(q);
    printf("\nSum : %d", sum);
    Sleep(500);
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->cmp = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->cmp = (cmp_f)GetProcAddress(dyn->hLib, "compare");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}

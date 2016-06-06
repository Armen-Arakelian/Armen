#include <stdlib.h>
#include <string.h>

#include "http.h"


 HTTP_REQUEST_TYPE getTypeByStr(const char * str);

struct KeyVal
{
    char key[256];
    char value[256];
};

struct http_s
{
    size_t formLen;
    char uriStr[256];
    struct KeyVal form[20];
    HTTP_REQUEST_TYPE type;
};

http_t http_new()
{
    return (http_t) malloc(sizeof(struct http_s));
}

void http_delete(http_t self)
{
    free(self);
}

const char * http_getArg(http_t self, const char * key)
{
    for (int i = 0; i < self->formLen; i++)
        {
        if(!strcmp(self->form[i].key, key))
            return self->form[i].value;
    }
    return NULL;
}

HTTP_REQUEST_TYPE getTypeByStr(const char * str)
{
    const char * repr[] = {"POST", "GET", "PUT", "HEAD", "DELETE", "CONNECT", "TRACE", "OPTIONS"};

    for(int i = 0; i < 8; i++)
    {
        if(!strcmp(str, repr[i])) return (HTTP_REQUEST_TYPE) i;
    }
    return 0;
}

HTTP_REQUEST_TYPE http_getType(http_t self)
{
    return self->type;
}

const char * http_getURI(http_t self)
{
    return self->uriStr;
}

char * http_getArgsNum(http_t self)
{
    return (char *)self->formLen;
}


const char * http_getKey(http_t self, unsigned int index)
{
    if(index >= 20) return "";
    else return self->form[index].key;
}

void http_parse(http_t self, const char * request)
{
    const int maxLen = 24;
    size_t methodLen = 0;
    methodLen = strstr(request, " ") - request;
    if(methodLen > maxLen || methodLen < 0)
        return;

    char str[256] = "";
    memcpy(str, request, methodLen);
    str[methodLen] = '\0';
    self->type = getTypeByStr(str);
    const char * uriFirstPtr = request + methodLen + 1;
    size_t uriLen = strstr(uriFirstPtr, " ") - uriFirstPtr;

    memcpy(self->uriStr, uriFirstPtr, uriLen);
    self->uriStr[uriLen] = '\0';

    if(self->type == HTTP_POST)
        {
        const char * firstFormPtr = NULL;
        firstFormPtr = strstr(uriFirstPtr, "\r\n\r\n");
        firstFormPtr += 4;

        char formStr[20 *(512)];
        strcpy(formStr, firstFormPtr);

        self->formLen = 0;
        for(char * str = strtok(formStr, "&"); str != NULL; str = strtok(NULL, "&"))
        {
            size_t keyLen = strstr(str, "=") - str;
            memcpy(self->form[self->formLen].key, str, keyLen);
            self->form[self->formLen].key[keyLen] = '\0';
            strcpy(self->form[self->formLen].value, str + keyLen + 1);
            self->formLen++;
        }
    }
}


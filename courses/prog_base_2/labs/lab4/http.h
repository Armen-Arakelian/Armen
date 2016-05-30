#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

typedef struct http_s * http_t;

typedef enum HTTP_REQUEST_TYPE{HTTP_POST, HTTP_GET, HTTP_PUT, HTTP_HEAD, HTTP_DELETE, HTTP_CONNECT, HTTP_TRACE, HTTP_OPTIONS } HTTP_REQUEST_TYPE;

http_t http_new();
void http_delete(http_t self);

const char * http_getArg(http_t self, const char * key);
HTTP_REQUEST_TYPE http_getType(http_t self);
const char * http_getURI(http_t self);
const char * http_getArgsNum(http_t self);
const char * http_getKey(http_t self, unsigned int index);
void http_parse(http_t self, const char * request);

#endif // HTTP_H_INCLUDED

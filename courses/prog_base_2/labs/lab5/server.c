#include <string.h>

#include "socket.h"
#include "server.h"
#include "http.h"
#include "convertor.h"

struct server_s
{
    DataHandler_t dataHandler;
    socket_t * serverSock;
};

enum SERVER_ERROR
{
    SERVER_OK,
    SERVER_FILE_ERROR,
    SERVER_INDEX_ERROR,
    SERVER_KEY_ERROR,
    SERVER_VALUE_ERROR,
    SERVER_ARGS_ERROR
};

typedef enum SERVER_ERROR SERVER_ERROR;

int isAlpha(const char * str);
int isAlphaNum(const char * str);
int isNonNegatInteger(const char * str);
int isNonNegatReal(const char * str);
int isInteger(const char * str);
int isReal(const char * str);
int isDate(const char * str);
char * getTok(const char * str, unsigned int index, const char * delimeters, char * memPtr);


static SERVER_ERROR _checkArgs(http_t httpReq, socket_t * clientSock);
static SERVER_ERROR _checkIndex(server_t self, int index);
static SERVER_ERROR _checkKeyValue(const char * key, const char * value);

static const char * const httpSuccessReplyStrFormat =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text\r\n"
        "Content-Length: %zu\r\n\r\n"
        "%s";

static const char * const httpInvalidUriReplyStrFormat =
        "HTTP/1.1 404 INVALID_URI\r\n"
        "Content-Type: text\r\n"
        "Content-Length: %zu\r\n\r\n"
        "%s";

static const char * const httpInvalidKeyReplyStrFormat =
        "HTTP/1.1 401 INVALID_KEY\r\n"
        "Content-Type: text\r\n"
        "Content-Length: %zu\r\n\r\n"
        "%s";

static const char * const httpInvalidValueReplyStrFormat =
        "HTTP/1.1 402 INVALID_VALUE\r\n"
        "Content-Type: text\r\n"
        "Content-Length: %zu\r\n\r\n"
        "%s";

static const char * const httpMethtodValueReplyStrFormat =
        "HTTP/1.1 400 INVALID_METHOD\r\n"
        "Content-Type: text\r\n"
        "Content-Length: %zu\r\n\r\n"
        "%s";

static const char * const httpOptionsOkStr =
            "HTTP/1.1 200 OK\n"
            "Access-Control-Allow-Origin: *\n"
            "Access-Control-Allow-Methods: DELETE\n"
            "\n";

static const char * const htmlDocStrFormat =
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<meta charset=\"ASCI\">"
        "%s"
        "</head>"
        "<body>"
        "%s"
        "</body>"
        "</html>";


int isAlpha(const char * str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if(!isalpha(str[i])) return 0;
    }
    return 1;
}

int isAlphaNum(const char * str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if(!isalnum(str[i])) return 0;
    }
    return 1;
}

int isNonNegatInteger(const char * str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if(!isdigit(str[i])) return 0;
    }
    return 1;
}

int isNonNegatReal(const char * str){
    int dot = 0;
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if(str[i] == '.'){
             if(!dot) dot = 1;
             else return 0;
        } else if(!isdigit(str[i])) return 0;
    }
    return 1;
}

int isDate(const char * str){
    if(strlen(str) > 15) return 0;
    char buff[16];

    getTok(str, 0, "-", buff);
    if(!isNonNegatInteger(buff) || strlen(buff) != 4) return 0;

    getTok(str, 1, "-", buff);
    if(!isNonNegatInteger(buff) || strlen(buff) != 2 || atoi(buff) > 12) return 0;

    getTok(str, 2, "-", buff);
    if(!isNonNegatInteger(buff) || strlen(buff) != 2 || atoi(buff) > 31) return 0;

    getTok(str, 3, "-", buff);
    if(strlen(buff) != 0) return 0;

    return 1;
}

char * getTok(const char * str, unsigned int index, const char * delimeters, char * memPtr)
{
    char buff[500];
    strcpy(buff, str);

    int i = 0;
    for (char * tok = strtok(buff, delimeters); tok != NULL; i++, tok = strtok(NULL, delimeters))
    {
        if(i == index)
        {
            strcpy(memPtr, tok);
            return memPtr;
        }
    }
    strcpy(memPtr, "");
    return memPtr;
}


static void _reply(server_t self, http_t httpRequest, socket_t * clientSock);
static void _writePatients_XML(server_t self, socket_t * clientSock);
static void _writePatient_XML(server_t self, socket_t * clientSock, unsigned int index);
static void _emptySuccessReply(socket_t * clientSock);
static void _successDeleteReply(socket_t * clientSock, unsigned int index);
static void _successUpdateReply(socket_t * clientSock, unsigned int index);
static void _optionsOkReply(socket_t * clientSock);
static void _successAdditionReply(socket_t * clientSock);
static void _replyInvalidUri(socket_t * clientSock);
static void _replyInvalidMethod(socket_t * clientSock);
static void _replyInvalidIndex(socket_t * clientSock, unsigned int index);
static void _replyInvalidKey(socket_t * clientSock, const char * key);
static void _replyInvalidValue(socket_t * clientSock, const char * value);
static void _replyInvalidArgsNum(socket_t * clientSock);
static void _replyHomepage_HTML(server_t self, socket_t * clientSock);
static void _writePatients_HTML(server_t self, socket_t * clientSock);
static void _writePatient_HTML(server_t self, socket_t * clientSock, unsigned int index);
static void _replyNewPatient_HTML(server_t self, socket_t * clientSock);

static void _addPatientIfPossible(server_t self, socket_t * clientSock, http_t httpRequest);

static SERVER_ERROR _checkArgs(http_t httpRequest, socket_t * clientSock);
static SERVER_ERROR _checkIndex(server_t self, int index);
static SERVER_ERROR _checkKeyValue(const char * key, const char * value);

server_t server_new(int port){
    server_t self = (server_t) malloc(sizeof(struct server_s));
    self->dataHandler = DataHandler_new("db.db");
    self->serverSock = socket_new();
    socket_bind(self->serverSock, port);
    socket_listen(self->serverSock);

    return self;
}

void server_delete(server_t self){
    free(self);
}

void server_listen(server_t self){
    char input[8000];

    http_t httpRequest = http_new();
    while(1) {
        socket_t * clientSock = socket_accept(self->serverSock);
        socket_read(clientSock, input, sizeof(input));

        http_parse(httpRequest, input);

        _reply(self, httpRequest, clientSock);

        socket_free(clientSock);
    }
}

static void _reply_XML(server_t self, http_t httpRequest, socket_t * clientSock){
    const char * uri = http_getURI(httpRequest);
    HTTP_REQUEST_TYPE type = http_getType(httpRequest);

    char child1[128], child2[128];
    getTok(uri, 1, "/", child1);
    getTok(uri, 2, "/", child2);

    if (!strcmp(child1, "patients")) {
        if(!strcmp(child2, "")){
            if (type == HTTP_GET){
                _writePatients_XML(self, clientSock);
            }else if (type == HTTP_POST){
                _addPatientIfPossible(self, clientSock, httpRequest);
            }else{
               _replyInvalidMethod(clientSock);
            }
        }else if (isNonNegatInteger(child2)){
            int index = atoi(child2);

            if(_checkIndex(self, index) == SERVER_INDEX_ERROR){
                _replyInvalidIndex(clientSock, index);
            }else{
                if (type == HTTP_GET){
                    _writePatient_XML(self, clientSock, index);
                } else if(type == HTTP_OPTIONS){
                    _optionsOkReply(clientSock);
                } else if (type == HTTP_DELETE){
                    DataHandler_deletePatient(self->dataHandler, index);
                    _successDeleteReply(clientSock, index);
                }else{
                    _replyInvalidMethod(clientSock);
                }
            }
        }else{
            _replyInvalidUri(clientSock);
        }
    }else{
        _replyInvalidUri(clientSock);
    }
}

static void _reply_HTML(server_t self, http_t httpRequest, socket_t * clientSock){
    const char * uri = http_getURI(httpRequest);
    HTTP_REQUEST_TYPE type = http_getType(httpRequest);

    char child0[128], child1[128];
    getTok(uri, 0, "/", child0);
    getTok(uri, 1, "/", child1);

    if (!strcmp(child0, "")) {
        if (type == HTTP_GET){
            _replyHomepage_HTML(self, clientSock);
        }else{
            _replyInvalidMethod(clientSock);
        }
    }else if (!strcmp(child0, "patients")){
        if(!strcmp(child1, "")){
            if (type == HTTP_GET){
                _writePatients_HTML(self, clientSock);
            }else if (type == HTTP_POST){
                _addPatientIfPossible(self, clientSock, httpRequest);
            }else{
               _replyInvalidMethod(clientSock);
            }
        }else if(isNonNegatInteger(child1)){
            int index = atoi(child1);

            if(_checkIndex(self, index) == SERVER_INDEX_ERROR){
                _replyInvalidIndex(clientSock, index);
            }else{
                if (type == HTTP_GET){
                    _writePatient_HTML(self, clientSock, index);
                }else if(type == HTTP_OPTIONS){
                    _optionsOkReply(clientSock);
                }else if (type == HTTP_DELETE){
                    DataHandler_deletePatient(self->dataHandler, index);
                    _successDeleteReply(clientSock, index);
                }else{
                   _replyInvalidMethod(clientSock);
                }
            }
        }else{
            _replyInvalidUri(clientSock);
        }
    }else if (!strcmp(child0, "new-patient")){
        if (type == HTTP_GET){
            _replyNewPatient_HTML(self, clientSock);
        }else{
            _replyInvalidMethod(clientSock);
        }
    }else{
        _replyInvalidUri(clientSock);
    }
}

static void _reply(server_t self, http_t httpRequest, socket_t * clientSock){
    const char * uri = http_getURI(httpRequest);

    char root[128];
    getTok(uri, 0, "/", root);

    if (!strcmp(root, "api")) {
        _reply_XML(self, httpRequest, clientSock);
    } else if (!strcmp(root, "favicon.ico")){
        _emptySuccessReply(clientSock);
    }else{
        _reply_HTML(self, httpRequest, clientSock);
    }
}

static void _replyHomepage_HTML(server_t self, socket_t * clientSock){
    char buff[512];
    char buff1[512];
    char res[512];
    strcpy(buff, "<h1>Welcome to hospital!!!</h1><br>"
           "<a href=\"/patients\">list of patients</a>");
    sprintf(buff1, htmlDocStrFormat, "", buff);
    sprintf(res, httpSuccessReplyStrFormat, strlen(buff1), buff1);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

 void _writePatients_HTML(server_t self, socket_t * clientSock){
    char buff[10000] = "";
    char buff1[10000] = "";
    char res[10000] = "";

    strcpy(buff, "<a><b>patients:</b></a><br><ol type=\"1\" start=\"0\">");

    int invsNum = DataHandler_getPatientsNum(self->dataHandler);

    void _foreachPat_appendPat_HTML(patient_t pt){
        char buff2[256];
        sprintf(buff2, "<li><a href=\"/patients/%d\">%s %s<a></li>", pt->id, pt->name, pt->disease);
        strcat(buff, buff2);
    }

    DataHandler_foreachPat(self->dataHandler, _foreachPat_appendPat_HTML);

    strcat(buff, "</ol><a href=\"/new-patient\">new</a>");

    sprintf(buff1, htmlDocStrFormat, "", buff);
    sprintf(res, httpSuccessReplyStrFormat, strlen(buff1), buff1);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _writePatient_HTML(server_t self, socket_t * clientSock, unsigned int index){
    char buff[1000] = "";
    char buff1[1000] = "";
    char res[1000] = "";

    patient_t pt = DataHandler_getPatient(self->dataHandler, index);
    patient_ConvertToString(pt, buff1);
    sprintf(buff, "<a>%s</a><br><a href=\"#\" onclick=\"doDelete()\">Delete</a>"
            "<script>"
            "function doDelete(){"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/patients/%d\", true);"
                "xhttp.send();"
            "}"
            "</script>", buff1, index);

    sprintf(buff1, htmlDocStrFormat, "", buff);
    sprintf(res, httpSuccessReplyStrFormat, strlen(buff1), buff1);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

void _replyNewPatient_HTML(server_t self, socket_t * clientSock){
    char buff[2000] = "";
    char buff1[2000] = "";
    char res[2000] = "";

    strcpy(buff, "<form action=\"/patients\" method=\"POST\">"
            "<fieldset>"
                "<legend>Patient</legend>"
                "name:<br>"
                "<input type=\"text\" name=\"name\"><br>"
                "disease:<br>"
                "<input type=\"text\" name=\"disease\"><br>"
                "time:<br>"
                "<input type=\"number\" name=\"time\" min=\"0\"><br>"
                "hospitalisedDate:<br>"
                "<input type=\"text\" name=\"hospitalisedDate\"><br>"
                "mass:<br>"
                "<input type=\"text\" name=\"mass\"><br>"
                "<input type=\"submit\" value=\"submit\"><br>"
            "</fieldset>"
            "</form>");

    sprintf(buff1, htmlDocStrFormat, "", buff);
    sprintf(res, httpSuccessReplyStrFormat, strlen(buff1), buff1);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static SERVER_ERROR _checkIndex(server_t self, int index){
    if(DataHandler_getPatient(self->dataHandler, index) == NULL) return SERVER_INDEX_ERROR;
    else return SERVER_OK;
}

static void _emptySuccessReply(socket_t * clientSock){
    char res[64];
    sprintf(res, httpSuccessReplyStrFormat, 0, "");

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _successDeleteReply(socket_t * clientSock, unsigned int index){
    char buff[64];
    char res[128];
    sprintf(buff, "Patient %zu was successfully deleted", index);
    sprintf(res, httpSuccessReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _successAdditionReply(socket_t * clientSock){
    char buff[64];
    char res[128];
    strcpy(buff, "Patient was successfully added");
    sprintf(res, httpSuccessReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _successUpdateReply(socket_t * clientSock, unsigned int index){
    char buff[64];
    char res[128];
    sprintf(buff, "Patient %zu was successfully updated", index);
    sprintf(res, httpSuccessReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _replyInvalidUri(socket_t * clientSock){
    char buff[16];
    char res[80];
    strcpy(buff, "INVALID URI");
    sprintf(res, httpInvalidUriReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _replyInvalidMethod(socket_t * clientSock){
    char buff[16];
    char res[80];
    strcpy(buff, "INVALID METHOD");
    sprintf(res, httpMethtodValueReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _replyInvalidIndex(socket_t * clientSock, unsigned int index){
    char buff[24];
    char res[80];
    sprintf(buff, "INVALID INDEX: %zu", index);
    sprintf(res, httpInvalidUriReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _replyInvalidKey(socket_t * clientSock, const char * key){
    char buff[256];
    char res[320];
    sprintf(buff, "INVALID KEY: %s", key);
    sprintf(res, httpInvalidKeyReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _replyInvalidValue(socket_t * clientSock, const char * value){
    char buff[256];
    char res[320];
    sprintf(buff, "INVALID VALUE: %s", value);
    sprintf(res, httpInvalidValueReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _optionsOkReply(socket_t * clientSock){
    socket_write_string(clientSock, httpOptionsOkStr);
    socket_close(clientSock);
}

static void _replyInvalidArgsNum(socket_t * clientSock){
    char buff[64];
    char res[128];
    strcpy(buff, "NOT ALL FIELDS");
    sprintf(res, httpInvalidValueReplyStrFormat, strlen(buff), buff);

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

static void _writePatients_XML(server_t self, socket_t * clientSock){
    char str[10000];
    str[0] = '\0';
    char res[10000];

    sprintf(res, httpSuccessReplyStrFormat, strlen(str), DataHandler_patientsToXmlStr(self->dataHandler, str));

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

void _writePatient_XML(server_t self, socket_t * clientSock, unsigned int index){
    char str[1000];
    str[0] = '\0';
    char res[1000];
    sprintf(res, httpSuccessReplyStrFormat, strlen(str), patient_convertToXmlString(DataHandler_getPatient(self->dataHandler, index), str));

    socket_write_string(clientSock, res);
    socket_close(clientSock);
}

void _addPatientIfPossible(server_t self, socket_t * clientSock, http_t httpRequest){
    int argsNum = http_getArgsNum(httpRequest);
            if(argsNum < 5){
                _replyInvalidArgsNum(clientSock);
            }else if(_checkArgs(httpRequest, clientSock) == SERVER_OK){
                patient_t pt = patient_new();
                for(int i = 0; i < argsNum; i++){
                    const char * key = http_getKey(httpRequest, i);
                    const char * val = http_getArg(httpRequest, key);

                    patient_setParametr(pt, key, val);

                }
                DataHandler_addPatient(self->dataHandler, pt);
                _successAdditionReply(clientSock);
                patient_delete(pt);
            }
}

static SERVER_ERROR _checkArgs(http_t httpRequest, socket_t * clientSock){
    int argsNum = http_getArgsNum(httpRequest);
    for(int i = 0; i < argsNum; i++){
        const char * key = http_getKey(httpRequest, i);
        const char * val = http_getArg(httpRequest, key);
        SERVER_ERROR err = _checkKeyValue(key, val);
        if(err == SERVER_KEY_ERROR){
            _replyInvalidKey(clientSock, key);
            return SERVER_ARGS_ERROR;
        } else if (err == SERVER_VALUE_ERROR){
            _replyInvalidValue(clientSock, val);
            return SERVER_ARGS_ERROR;
        }
    }
    return SERVER_OK;
}


static SERVER_ERROR _checkKeyValue(const char * key, const char * value){
    int keyLen = strlen(key);
    int valLen = strlen(value);
    if(valLen == 0 || valLen > 23 || keyLen == 0 || keyLen > 23){
        return SERVER_VALUE_ERROR;
    }

    if(!strcmp(key, "name") || !strcmp(key, "disease")){
        if(!isAlpha(value)){
            return SERVER_VALUE_ERROR;
        }
        }else if(!strcmp(key, "time")){
        if(!isNonNegatInteger(value)){
            return SERVER_VALUE_ERROR;
        }
    }else if(!strcmp(key, "hospitalisedDate")){
        if(!isDate(value)){
            return SERVER_VALUE_ERROR;
        }
    }else if(!strcmp(key, "mass")){
        if(!isNonNegatReal(value)){
            return SERVER_VALUE_ERROR;
        }
    }else if(!strcmp(key, "mass")){
        if(!isNonNegatReal(value)){
            return SERVER_VALUE_ERROR;
        }
    }else{
        return SERVER_KEY_ERROR;
    }
    return SERVER_OK;
}

#include<stdio.h>
#include<winsock2.h>
#include <string.h>

#pragma comment(lib,"ws2_32.lib")

#define PORT 80
#define MAX_REP_LEN 20480

void getName(char * buf, char * result);

int main(int argc , char *argv[])
{
const char * hostName  = "pb-homework.appspot.com";
WSADATA wsa;
SOCKET s;
struct sockaddr_in server;
char server_reply[MAX_REP_LEN];
int recv_size;

printf("\nInitialising Winsock...");
if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
{
printf("Failed. Error Code : %d",WSAGetLastError());
return 1;
}
printf("Initialised.\n");

if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
{
printf("Could not create socket : %d" , WSAGetLastError());
}

printf("Socket created.\n");

server.sin_addr.s_addr = inet_addr("216.58.214.241");
server.sin_family = AF_INET;
server.sin_port = htons(PORT);

int code;
if ((code = connect(s, (struct sockaddr *)&server , sizeof(server))) < 0)
{
printf("Error code: %d", code);
return 1;
}
puts("Connected");

char request[200];
firstRequest(s, request, hostName);

getSecret(s, server_reply, &recv_size);

secondRequest(s, request, server_reply, hostName);


char * result[200];
getResultName(s, server_reply, result, &recv_size);

thirdRequest(s, request, server_reply, result, hostName);

getResult(s, server_reply, recv_size);

closesocket(s);
WSACleanup();
return 0;
}


void sendReq(SOCKET s, char * request, int len)
{
    if( send(s , request , len , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Sent\n");
}


int Recv(SOCKET s, char * server_reply)
{
    int recv_size;
    if((recv_size = recv(s , server_reply , MAX_REP_LEN , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }
    puts("\nReply received");
    return recv_size;
}

void firstRequest(SOCKET s, char * request, const char * hostName)
{
    sprintf(request, "GET /var/1 HTTP/1.1\r\nHost:%s\r\n\r\n", hostName);
    sendReq(s, request, strlen(request));
}

void getSecret(SOCKET s, char * server_reply, int * recv_size)
{
    *recv_size = Recv(s, server_reply);
    strcpy(server_reply, strstr(server_reply, "secret="));
}


void secondRequest(SOCKET s, char * request, char * server_reply, const char * hostName)
{
    sprintf(request, "GET /var/1?%s HTTP/1.1\r\nHost:%s\r\n\r\n", server_reply, hostName);
    sendReq(s, request, strlen(request));
}

void getResultName(SOCKET s, char * server_reply, char * result, int * recv_size)
{
    *recv_size = Recv(s, server_reply);
    server_reply[*recv_size] = '\0';
    printf("%s", server_reply);
    strcpy(server_reply - 4, strstr(server_reply, "\r\n\r\n"));
    char name[100];
    getName(server_reply, name);
    printf("\n%s", name);
    sprintf(result, "result=%s", name);
}

void thirdRequest(SOCKET s, char * request, char * server_reply, char * result, const char * hostName)
{
    sprintf(request, "POST /var/1 HTTP/1.1\r\nHost:%s\r\nContent-Length: %d\r\n\r\n%s", hostName, strlen(result), result);
    sendReq(s, request, strlen(request));
}


void getResult(SOCKET s, char * server_reply, int recv_size)
{
    recv_size = Recv(s, server_reply);
    server_reply[recv_size] = '\0';
    printf("\n%s", server_reply);
}

#include<stdio.h>
#include<winsock2.h>
#include <string.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define PORT 80
#define MAX_REP_LEN 20480

char * getName(char * buf);

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

//Create a socket
if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
{
printf("Could not create socket : %d" , WSAGetLastError());
}

printf("Socket created.\n");

server.sin_addr.s_addr = inet_addr("216.58.214.241");
server.sin_family = AF_INET;
server.sin_port = htons(PORT);

//Connect to remote server
int code;
if ((code = connect(s, (struct sockaddr *)&server , sizeof(server))) < 0)
{
printf("Error code: %d", code);
return 1;
}
puts("Connected");

char request[200];

sprintf(request, "GET /var/1 HTTP/1.1\r\nHost:%s\r\n\r\n", hostName);
if( send(s , request , strlen(request) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
puts("Data Sent\n");

//Receive a reply from the server
if((recv_size = recv(s , server_reply , MAX_REP_LEN , 0)) == SOCKET_ERROR)
{
puts("recv failed");
}
puts("\nReply received");

strcpy(server_reply, strstr(server_reply, "secret="));

sprintf(request, "GET /var/1?%s HTTP/1.1\r\nHost:%s\r\n\r\n", server_reply, hostName);
if( send(s , request , strlen(request) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
puts("Data Sent\n");
if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
{
puts("recv failed");
}
puts("\nReply received");
server_reply[recv_size] = '\0';
printf("%s", server_reply);
strcpy(server_reply - 4, strstr(server_reply, "\r\n\r\n"));
char * name = getName(server_reply);
printf("\n%s", name);
char result[100];
sprintf(result, "result=%s", name);
sprintf(request, "POST /var/1 HTTP/1.1\r\nHost:%s\r\nContent-Length: %d\r\n\r\n%s", hostName, strlen(result), result);
if(send(s, request, strlen(request), 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }
server_reply[recv_size] = '\0';
printf("\n%s", server_reply);
closesocket(s);
WSACleanup();
return 0;
}



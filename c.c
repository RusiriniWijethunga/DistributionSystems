
//This is the client program in C that sets up a TCP connection using the Windows-specific Winsock library. 
#include <stdio.h>
#include <stdlib.h> //stdlib.h: For standard utility functions like exit.
#include <string.h> //string.h: To handle string operations, like copying or comparing strings.
#include <winsock2.h> //use win socke2.h for windows and and contains functions for network programming (like creating sockets).

#define port 5050

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer [1024] = {0};

    //initialize win socket
    if (WSAStartup(MAKEWORD(2,2), &wsa) !=0);{
        printf("Failed. Error code: %d", WSAGetLastError());
        return 1;
    }

    //creating socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        printf("Socket creation fauled. Error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.101.223"); //use inet_addr for simplicity

    //connecting to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("Connection Failed. Error:%d\n", WSAGETlASTeRROR());
        closesocket(sock);
        WSACleanup();
    }


}

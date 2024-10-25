
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>  // Use winsock2.h for Windows

#define PORT 5050

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Creating socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed. Error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.101.223");  // Use inet_addr for simplicity

    // Connecting to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed. Error: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Sending message to server
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Receiving message from server
    recv(sock, buffer, 1024, 0);
    printf("Message from server: %s\n", buffer);

    // Closing the socket for client
    closesocket(sock);
    WSACleanup();  // Cleanup Winsock

    return 0;
}

//gcc client.c -o client.exe -lws2_32 (this command has to type)


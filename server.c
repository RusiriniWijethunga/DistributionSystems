#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> 

#define PORT 5050

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    // Creating socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed. Error: %d", WSAGetLastError());
        return 1;
    }

    // Binding to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Bind failed. Error: %d", WSAGetLastError());
        return 1;
    }

    // Listening for clients
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed. Error: %d", WSAGetLastError());
        return 1;
    }

    printf("Server is listening on port %d\n", PORT);

    // Accepting client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
        printf("Accept failed. Error: %d", WSAGetLastError());
        return 1;
    }

    // Receiving message from client
    recv(new_socket, buffer, 1024, 0);
    printf("Message from client: %s\n", buffer);

    // Sending response to client
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Close the sockets
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();  // Cleanup Winsock

    return 0;
}

//gcc server.c -o server.exe -lws2_32 (this command has to type)

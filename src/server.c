#include "server.h" //  start_server
#include <stdio.h>  //  printf
#include <stdlib.h> //  EXIT tags
#include <sys/socket.h> // socket

static int server_socket;
static struct sockaddr_un server_addr;
static int client_socket;              // Not scalable
static struct sockaddr_un client_addr; // Not scalable
unsigned int slen = sizeof(server_addr);
unsigned int clen = sizeof(client_addr);

void start_server(int port){
    // Testea buen import/call desde main
    printf("[server] Running in port %d...\n", port);

    // Config Socket boilerplate
    server_addr.sun_family = AF_UNIX;
    
    snprintf(server_addr.sun_path, 
             sizeof(server_addr.sun_path),
             "%s",
             "unix_socket");      
    unlink(server_addr.sun_path);
    
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (bind(server_socket, (struct sockaddr *) &server_addr, slen) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 1) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("[server] Waiting for connection...\n");
}

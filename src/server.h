#ifndef SERVER_H
#define SERVER_H

#include <unistd.h> // size_t

#define MAX_CLIENTS 10
#define USERNAME_MAX 32
#define SOMAXCONN 16
#define INBUF_SIZE 1024
#define INT_MAX 10

typedef struct Client
{
    int socket;  // -1 means unused
    int room_id; // -1 if not in a room
    int index;   // owned identity
    char username[USERNAME_MAX];
    char inbuf[INBUF_SIZE];
    size_t inbuf_len;
} Client;

// Public server functions
void start_server(const char *socket_path);

//_Helpers
int find_free_client(void);
void clients_init(void);
void client_init(Client *c, int idx);
void client_remove(Client *c);

void broadcast_join(int room_id, Client *c);
void broadcast_leave(int room_id, Client *c);
void broadcast_room(int room_id, Client *sender, const char *msg, size_t len);
void broadcast_msg(int room_id, Client *sender, const char *msg, size_t len);

#endif // SERVER_H
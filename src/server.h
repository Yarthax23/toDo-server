#ifndef SERVER_H
#define SERVER_H

#include <sys/un.h>

#define MAX_CLIENTS 10

// Public server functions
void start_server(int port);
void broadcast_message(const char *msg);


#endif // SERVER_H
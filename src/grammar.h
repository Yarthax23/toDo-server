#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <unistd.h> // size_t

typedef enum
{
    CMD_NICK,
    CMD_JOIN,
    CMD_LEAVE,
    CMD_MSG,
    CMD_QUIT,
    CMD_INVALID
} command_type;

typedef enum
{
    CMD_OK,           // Nothing to do
    CMD_DISCONNECT,   // Disconnect client
    CMD_SET_NICK,     // Client changes username
    CMD_JOIN_ROOM,    // Client changes room
    CMD_LEAVE_ROOM,   // Client left room
    CMD_BROADCAST_MSG // Broadcast payload
} command_result;

typedef struct
{
    command_result type; // What to do
    int room_id;         // JOIN/LEAVE; -1 means unused
    const char *payload; // MSG
    size_t payload_len;  // MSG
} command_action;

struct Client;
command_action handle_command(struct Client *c, const char *msg, size_t len);

#endif // GRAMMAR_H
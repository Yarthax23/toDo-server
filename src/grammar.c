#include "grammar.h"
#include "server.h" // Client

#include <errno.h>
#include <stdlib.h> // EXIT
#include <string.h> // mem*, str*

#define MAX_ROOM_ID 63

typedef struct
{
    const char *name;
    size_t len;
    command_type type;
} command_spec;

static const command_spec command_table[] = {
    {"NICK", 4, CMD_NICK},
    {"JOIN", 4, CMD_JOIN},
    {"LEAVE", 5, CMD_LEAVE},
    {"MSG", 3, CMD_MSG},
    {"QUIT", 4, CMD_QUIT}};

static const size_t command_table_len =
    sizeof(command_table) / sizeof(command_table[0]);

static command_type parse_command(const char *msg, size_t len, const char **args, size_t *args_len);
static command_action handle_nick(Client *c, const char *args, size_t args_len);
static command_action handle_join(Client *c, const char *args, size_t args_len);
static command_action handle_leave(Client *c, const char *args, size_t args_len);
static command_action handle_msg(Client *c, const char *args, size_t args_len);

static inline command_action action_ok(void);
static inline command_action action_disconnect(int old_room);
static inline command_action action_nick(const char *p, size_t len);
static inline command_action action_join(int new_room);
static inline command_action action_leave(int old_room);
static inline command_action action_broadcast(const char *p, size_t len);

command_action handle_command(Client *c, const char *msg, size_t len)
{
    const char *args;
    size_t args_len;

    command_type cmd = parse_command(msg, len, &args, &args_len);

    switch (cmd)
    {
    case CMD_NICK:
        return handle_nick(c, args, args_len);
    case CMD_JOIN:
        return handle_join(c, args, args_len);
    case CMD_LEAVE:
        return handle_leave(c, args, args_len);
    case CMD_MSG:
        return handle_msg(c, args, args_len);
    case CMD_QUIT:
        if (args != NULL || args_len != 0)
            return action_disconnect(c->room_id); // protocol violation
        return action_disconnect(c->room_id);     // valid quit

    default:
        return action_disconnect(c->room_id);
    }

    // Unreachable, documents intent
    return action_ok();
}

static command_type parse_command(const char *msg, size_t len,
                                  const char **args, size_t *args_len)
{
    *args = NULL;
    *args_len = 0;
    // Extract command token
    const char *space = memchr(msg, ' ', len);
    size_t cmd_len = space ? (size_t)(space - msg) : len;

    for (size_t i = 0; i < command_table_len; i++)
    {
        const command_spec *spec = &command_table[i];

        // Validate command name
        if (cmd_len == spec->len &&
            memcmp(msg, spec->name, spec->len) == 0)
        {
            if (space)
            {
                *args = space + 1;
                *args_len = len - (cmd_len + 1);
            }
            return spec->type;
        }
    }

    return CMD_INVALID;
}

static command_action handle_nick(Client *c, const char *args, size_t args_len)
{
    // Missing argument
    if (!args)
        goto error;

    // Empty argument
    if (!args_len)
        goto error;

    // Too long
    if (args_len >= USERNAME_MAX)
        goto error;

    // Contains spaces
    if (memchr(args, ' ', args_len))
        goto error;

    return action_nick(args, args_len);

error:
    return action_disconnect(c->room_id);
}

static command_action handle_join(Client *c, const char *args, size_t args_len)
{
    // Missing argument
    if (!args)
        goto error;

    // Empty argument
    if (!args_len)
        goto error;

    char buf[32];
    if (args_len >= sizeof(buf))
        goto error;

    memcpy(buf, args, args_len);
    buf[args_len] = '\0';

    errno = 0;
    char *end = NULL;
    long room = strtol(buf, &end, 10);

    // No digits
    if (end == buf)
        goto error;

    // Trailing garbage (strict grammar)
    if (*end != '\0')
        goto error;

    // Out of range
    if ((errno == ERANGE) || room < 0 || room > MAX_ROOM_ID)
        goto error;

    // Same room
    if (c->room_id == (int)room)
        return action_ok();

    // Join new room
    return action_join((int)room);

error:
    return action_disconnect(c->room_id);
};

static command_action handle_leave(Client *c, const char *args, size_t args_len)
{
    // Extra arguments
    if (args || args_len)
        goto error;

    // Already in no-room
    if (c->room_id == -1)
        return action_ok();

    return action_leave(c->room_id);
error:
    return action_disconnect(c->room_id);
};

static command_action handle_msg(Client *c, const char *args, size_t args_len)
{
    // Not in a room
    if (c->room_id < 0)
        goto error;

    // Missing payload
    if (!args)
        goto error;

    return action_broadcast(args, args_len);
error:
    return action_disconnect(c->room_id);
};

// Helper constructors (Macros so handlers stay readable)
static inline command_action action_ok(void)
{
    return (command_action){.type = CMD_OK, .room_id = -1};
}

static inline command_action action_disconnect(int old_room)
{
    return (command_action){.type = CMD_DISCONNECT, .room_id = old_room};
}

static inline command_action action_nick(const char *p, size_t len)
{
    return (command_action){.type = CMD_SET_NICK, .room_id = -1, .payload = p, .payload_len = len};
}

static inline command_action action_join(int new_room)
{
    return (command_action){.type = CMD_JOIN_ROOM, .room_id = new_room};
}

static inline command_action action_leave(int old_room)
{
    return (command_action){.type = CMD_LEAVE_ROOM, .room_id = old_room};
}

static inline command_action action_broadcast(const char *p, size_t len)
{
    return (command_action){.type = CMD_BROADCAST_MSG, .room_id = -1, .payload = p, .payload_len = len};
}

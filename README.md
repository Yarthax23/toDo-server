# TCP Chat in C
Personal project to learn sockets, synchronization, and systems programming fundamentals.

## Description
A multi-client chat server where each connected client can send messages, receive messages from others, and join or leave freely.
The server must support multiple clients concurrently and broadcast messages to all participants.

## Protocol (summary)
- Text messages terminated with `'\n'`
- `/rooms` command to list available rooms
- `/join <room>` to join a room

## How to build
make all

## How to run
make run

## Project Structure
```
├── app/
│   └── main.c              # Application entry point
├── docs/
│   └── standards.md        # Internal conventions, templates
├── src/
│   └── app.c               # Interactive application logic
├── test/
├── NOTES.md                # Personal notes, scratchpad
├── PROJECT_LOG.md          # Daily progress log
├── README.md               # This file
├── Makefile                # Build automation
└── .gitignore             
```


## Estado
Dia 1: repository created. Project currently in planning phase.
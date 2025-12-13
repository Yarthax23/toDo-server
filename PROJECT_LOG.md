## 2025-13-12 –  Day Three
### **Summary**

...

### **Decisions**

* ...

### **Added**

* ...

### **Changed**

* ...

### **Removed**

* ...

### **Learnings**

* ...

### **Next steps**

* [ ] ...

### **Notes**

* ...


## 2025-12-12 –  Initial server module setup
### **Summary**

Set up the initial server module with start_server(), integrated it in main.c, updated Makefile to simplify header includes, and documented decisions and configuration changes in PROJECT_LOG.

### **Decisions**

* Use snake_case instead of CamelCase (implemented via new macro).

### **Added**

* `server.h`, `server.c`.
* `keybindings.json` to make Shift+Space type underscore `_` in VS Code (Multi Command).
* `'I./src` CFLAG to make `#include` simple & concise.

### **Changed**

* `settings.json` to define macro for inserting `_`.

### **Removed**

* ...

### **Learnings**

* Reviewed Sockets documentation, boilerplate & notes.
* Reviewed how often to commit
* Discovered `xev` command: a debugging & development tool to print X events.
* Keybindings in VS Code can override system keys if the command does not exist.

### **Next steps**

* [ ] Continue implementing server features in server.c / server.h.
* [ ] Decide whether to use select() or threads + mutex for concurrency.
* [ ] Explore select() for handling multiple clients concurrently.
* [ ] Implement basic client handling using select().
* [ ] Research sigaction() for proper signal handling in fork() (if needed in future).
* [ ] Begin implementing broadcast_message() function.

### **Notes**

* System-wide Shift+Space remapping on Linux is tricky with XKB; AutoKey is a safer alternative if needed.


## 2025-11-12 –  Initial setup
### **Summary**

Set up the initial repository structure and development workflow. Defined conventions, added build automation, and prepared the base layout for the upcoming TCP chat server.

### **Decisions**

* Use **English** for all public-facing documentation (`README`, `docs`, commit messages).
* Keep personal notes in Spanish inside `NOTES.md`.
* Use **Makefile** for build tasks (`make all`, `make run`, `make clean`).
* Use a `docs/` folder for standards, architecture, and protocol documentation.
* Adopt **Conventional Commits**.

### **Added**

* `Makefile` with build/run/clean targets
* `docs/standards.md` for project conventions
* Initial folder structure: `app`, `src`, `test`, `docs`
* Project planning in `README.md`
* `.gitignore` rules for C builds and binaries

### **Changed**

* Reorganized files into the new structure
* Cleaned repository layout to follow a long-term scalable pattern
* Improved documentation structure and naming

### **Removed**

* Temporary/unstructured files from the initial creation stage

### **Learnings**

* Clarified the difference between `README`, `NOTES`, `PROJECT_LOG`, and `docs/` as separate documentation layers.
* Understood why GitHub isn’t a “museum of finished projects” but a historical record of the process.
* Reviewed Conventional Commit types and how they map to real work.

### **Next steps**

* Implement the minimal TCP server with `socket()`, `bind()`, `listen()`, `accept()`.
* Decide between `select()` vs. threads + mutex for concurrency.
* Write the first architecture sketches for `/docs/architecture.md`.

### **Notes**

* Investigate options for client handling: blocking vs nonblocking sockets.
* Evaluate buffer sizes and message parsing strategy for line-based protocol.
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
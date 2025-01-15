File Operations:

> open(): Opens a file or creates it if it doesn't exist, returns a file descriptor.

> close(): Closes a file descriptor.

> read(): Reads data from a file descriptor into a buffer.

> write(): Writes data from a buffer to a file descriptor.

Memory Management:

> malloc(): Allocates dynamic memory of specified size, returns a pointer.

> free(): Deallocates previously allocated memory.

Error Handling:

> perror(): Prints a system error message based on the value of errno.

> strerror(): Returns a string describing the error code passed to it.

File/Permission Checking:

> access(): Checks whether the process can access a file with specific permissions.

File Descriptor Manipulation:


> dup(): Creates a copy of a file descriptor.

> dup2(): Creates a copy of a file descriptor using a specified number.

Process Management:

> execve(): Replaces current process with a new program.

> exit(): Terminates the calling process.

> fork(): Creates a new process (child) by duplicating the calling process (parent).

> wait(): Parent process waits for child process to terminate.

> waitpid(): Waits for a specific child process to change state.

File System Operations:

> pipe(): Creates a pipe for inter-process communication.

> unlink(): Removes a file name from the filesystem.
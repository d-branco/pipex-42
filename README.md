# Environment Pointer (`envp`) in C

In C, `envp` refers to the **environment pointer**—a parameter often passed to programs (such as the `main()` function) that provides access to the environment variables of the system. It is a pointer to an array of strings, where each string represents an environment variable in the format `KEY=VALUE`.

## Structure of `envp`

- **`envp` type**: `char **envp`
  - It's a pointer to an array of strings (`char *`), where each string is an environment variable. Specifically, `envp` points to the first element in this array.
  - In C, an array of strings is typically represented as `char **`, because each string is a `char *`, and the array itself is an array of `char *` pointers.

## Example of `envp`

Suppose the environment contains the following variables:

```
USER=John
HOME=/home/john
PATH=/usr/bin:/bin:/usr/sbin
SHELL=/bin/bash
```

In `envp`, these would be stored as an array of strings:

```c
envp[0] = "USER=John"
envp[1] = "HOME=/home/john"
envp[2] = "PATH=/usr/bin:/bin:/usr/sbin"
envp[3] = "SHELL=/bin/bash"
envp[4] = NULL // Null-terminated
```

- `envp` itself points to `envp[0]`, which is `"USER=John"`.
- Each element in `envp` is a string in the format `KEY=VALUE`.
- The array is **null-terminated**, meaning that the last element is `NULL`. This is similar to how strings in C are null-terminated (`'\0'`), but here it's used for the array.

## Accessing `envp`

You can access individual environment variables using `envp[]`. For example:

```c
char *user = getenv("USER");
```

However, when passing `envp` to a function like `main()`, you have direct access to the entire environment, and you can loop through it like so:

```c
for (int i = 0; envp[i] != NULL; i++) {
    printf("%s\n", envp[i]);  // Print each environment variable
}
```

## Common Environment Variables

Some common environment variables you'll encounter in `envp` include:

- **`PATH`**: Contains a colon-separated list of directories where executable programs are located. When you run a command in a terminal, the system looks through these directories to find the corresponding executable.
  
  Example: `PATH=/usr/bin:/bin:/usr/sbin`
  
- **`HOME`**: The path to the current user's home directory.
  
  Example: `HOME=/home/john`

- **`USER`**: The current username.
  
  Example: `USER=John`

- **`SHELL`**: The path to the current user's default shell.
  
  Example: `SHELL=/bin/bash`

- **`PWD`**: The current working directory.
  
  Example: `PWD=/home/john/projects`

## Using `envp` in `main()`

In the `main()` function of a program, `envp` is passed as an argument. Here's an example:

```c
int main(int ac, char **av, char **envp)
{
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}
```

This program will print out all environment variables passed to it, as `envp` is essentially the program's view of the environment at runtime.

## Modifying `envp`

While you can **read** from `envp`, you generally **cannot modify** it directly because environment variables are managed by the operating system. However, you can change or add environment variables using functions like `setenv()` or `putenv()`.

For example, using `setenv()`:

```c
setenv("MY_VAR", "SomeValue", 1); // Creates or modifies MY_VAR
```

## Special Environment Variables

- **`PATH`**: As mentioned earlier, `PATH` is one of the most commonly used environment variables. It tells the shell where to look for executable programs.
  
- **`LD_LIBRARY_PATH`**: This variable specifies directories where shared libraries should be searched for before the usual places.
  
- **`HOME`**: The path to the user's home directory.
  
- **`USER`**: The username of the currently logged-in user.

## `envp` vs. `environ`

In some programs, especially on Unix-like systems, you may encounter a global variable named `environ` instead of `envp`. Both represent the environment variables, but the usage is slightly different:
- **`envp`** is passed as a parameter to `main()`.
- **`environ`** is a global variable that is available throughout the program.

For example:

```c
extern char **environ; // Global environment pointer

int main() {
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    return 0;
}
```

Both `envp` and `environ` are typically used to access environment variables, and in many cases, they will contain the same data.

## Conclusion

- **`envp`** is an array of strings containing the environment variables.
- Each string follows the format `KEY=VALUE`, representing the name of the environment variable and its value.
- It is passed to programs (such as `main()`) to allow them to access the environment variables, which can include important system information like `PATH`, `HOME`, and `USER`.

---

# Input/Output Redirection

- **`<` Input redirection**
  - Takes input from a file as if from the command line.
  - The file must exist.
  
  Example:  
  ```bash
  $ sort < names.txt
  ```

- **`>` Output redirection**
  - Redirects the output of a command into a file.
  - Creates the file if it does not exist.
  
  Example:  
  ```bash
  $ pwd > whereami.txt
  ```
  
  Classic example:  
  ```bash
  $ echo "Hello world" > output.txt
  ```

- **Combining input and output redirection**  
  Example:  
  ```bash
  $ grep "pattern" < input.txt > results.txt
  ```

- **`&>` Redirects both standard output and errors**.

- **`>>` Append output redirection**
  - Appends at the end of the file. (Useful for logs.)

- **`<<` Here Document or Heredoc**
  - Input redirection that allows multiline input and is delimited.
  
  Example:  
  ```bash
  cat << EOF
  This is line 1
  This is line 2
  This is line 3
  EOF
  # Prints all three lines
  ```

## Documentation

For more details, refer to the [POSIX documentation](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07).

---

# File Operations

- **`open()`**: Opens a file or creates it if it doesn't exist, returns a file descriptor.
- **`close()`**: Closes a file descriptor.
- **`read()`**: Reads data from a file descriptor into a buffer.
- **`write()`**: Writes data from a buffer to a file descriptor.

# Memory Management

- **`malloc()`**: Allocates dynamic memory of specified size, returns a pointer.
- **`free()`**: Deallocates previously allocated memory.

# Error Handling

- **`perror()`**: Prints a system error message based on the value of `errno`.
- **`strerror()`**: Returns a string describing the error code passed to it.

# File/Permission Checking

- **`access()`**: Checks whether the process can access a file with specific permissions.

# File Descriptor Manipulation

- **`dup()`**: Creates a copy of a file descriptor.
- **`dup2()`**: Creates a copy of a file descriptor using a specified number.

# Process Management

- **`execve()`**: Replaces the current process with a new program.
- **`exit()`**: Terminates the calling process.
- **`fork()`**: Creates a new process (child) by duplicating the calling process (parent).
- **`wait()`**: Parent process waits for the child process to terminate.
- **`waitpid()`**: Waits for a specific child process to change state.

# File System Operations

- **`pipe()`**: Creates a pipe for inter-process communication.
- **`unlink()`**: Removes a file name from the filesystem.

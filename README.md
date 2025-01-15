/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   README.md                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:34:40 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/15 11:34:41 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Input output redirection
"<" Input redirection
	- takes input from a file as if from the command line.
	- the file must exist.
	example:	`$ sort < names.txt`
">" output redirection
	- redirects the output of a comman into a file.
	- creates the file if not existing.
	example: `$ pwd > whereami.txt`
	classic example: `$ echo "Hello world" > output.txt`
both can be combined. Example: `$ grep "pattern" < input.txt > results.txt`
"&>" redirects both standard output and errors.
">>" Append output redirection
	- appends at the end of the file. (Usefull for logs.)
"<<" "Here Document" or "heredoc"
	- input redirection that allow multiline and is delimited.
	example:
	´´´
	cat << EOF
	This is line 1
	This is line 2
	This is line 3
	EOF
	# Prints all three lines
	´´´
Documentation:
	https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07

File Operations:
open():		Opens a file or creates it if it doesn't exist, returns a file descriptor.
close():	Closes a file descriptor.
read():		Reads data from a file descriptor into a buffer.
write(): 	Writes data from a buffer to a file descriptor.

Memory Management:
malloc():	Allocates dynamic memory of specified size, returns a pointer.
free():		Deallocates previously allocated memory.

Error Handling:
perror():	Prints a system error message based on the value of errno.
strerror():	Returns a string describing the error code passed to it.

File/Permission Checking:
access():	Checks whether the process can access a file with specific permissions.

File Descriptor Manipulation:
dup():		Creates a copy of a file descriptor.
dup2():		Creates a copy of a file descriptor using a specified number.

Process Management:
execve():	Replaces current process with a new program.
exit():		Terminates the calling process.
fork():		Creates a new process (child) by duplicating the calling process (parent).
wait():		Parent process waits for child process to terminate.
waitpid():	Waits for a specific child process to change state.

File System Operations:
pipe():		Creates a pipe for inter-process communication.
unlink():	Removes a file name from the filesystem.

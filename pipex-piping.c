/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-piping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:34:55 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/21 09:13:40 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_output_file(char *file)
{
	int	fd_out;

	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("Failed to open output file");
		return (-1);
	}
	return (fd_out);
}

static int	*create_pipes(int num_cmd, int fd_out)
{
	int	*pipe_fd;
	int	i;

	pipe_fd = (int *)malloc(sizeof(int) * (2 * (num_cmd - 1)));
	if (!pipe_fd)
	{
		perror("Malloc failed");
		close(fd_out);
		return (NULL);
	}
	i = 0;
	while (i < num_cmd - 1)
	{
		if (pipe(pipe_fd + 2 * i) == -1)
		{
			handle_error("pipe failed", fd_out);
		}
		i++;
	}
	return (pipe_fd);
}

static void	close_all_pipes(int *pipe_fd, int num_cmd, int fd_out)
{
	int	i;

	i = 0;
	while (i < 2 * (num_cmd - 1))
	{
		close(pipe_fd[i]);
		i++;
	}
	close(fd_out);
}

static void	setup_pipeline(int num_cmd, char *file, int *fd_out, int **pipe_fd)
{
	*fd_out = open_output_file(file);
	if (*fd_out == -1)
		return ;
	*pipe_fd = create_pipes(num_cmd, *fd_out);
	if (!*pipe_fd)
	{
		close(*fd_out);
		return ;
	}
}

void	execute_pipeline(char ***cmd, int num_cmd, char **envp, char *file)
{
	int		fd_out;
	int		*pipe_fd;
	int		i;
	pid_t	pid;

	setup_pipeline(num_cmd, file, &fd_out, &pipe_fd);
	i = 0;
	while (i < num_cmd)
	{
		pid = fork();
		if (pid == -1)
			handle_error("fork failed", fd_out);
		if (pid == 0)
		{
			redirect_child(i, num_cmd, pipe_fd, fd_out);
			close_all_pipes(pipe_fd, num_cmd, fd_out);
			execute_cmd(cmd[i], envp);
			exit(1);
		}
		i++;
	}
	close_all_pipes(pipe_fd, num_cmd, fd_out);
	free(pipe_fd);
	wait_for_children(num_cmd);
}

/*
void	execute_pipeline(char ***cmd, int num_cmd, char **envp, char *file)
{
	int	i;
	int	j;
	int	pid;
	int	fd_out;  // File descriptor for output file
	int	*pipe_fd; // Array to hold pipe file descriptors
	
	// Open output file
	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("Failed to open output file");
		return;
	}
	pipe_fd = (int *) malloc(sizeof(int *) * (2 * (num_cmd - 1)));
	if (!pipe_fd)
	{
		perror("Malloc failed");
		close(fd_out);
		return;
	}
	i = 0;
	while (i < num_cmd - 1) // Create pipes
	{
		if (pipe(pipe_fd + 2 * i) == -1)
		{
			perror("pipe failed");
			close(fd_out);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < num_cmd) // Fork child processes
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			close(fd_out);
			exit(1);
		}
		if (pid == 0)
		{
			if (i > 0) // Redirect stdin for all cmd except the first
			{
				if (dup2(pipe_fd[2 * (i - 1)], STDIN_FILENO) == -1)
				{
					perror("dup2 failed");
					exit(1);
				}
			}
			if (i < num_cmd - 1) // Redirect stdout for all cmd except the last
			{
				if (dup2(pipe_fd[2 * i + 1], STDOUT_FILENO) == -1)
				{
					perror("dup2 failed");
					exit(1);
				}
			}
			else // For the last command, redirect stdout to the file
			{
				if (dup2(fd_out, STDOUT_FILENO) == -1)
				{
					perror("dup2 failed");
					exit(1);
				}
			}
			j = 0;
			// Close all pipe file descriptors in the child
			while (j < 2 * (num_cmd - 1))
			{
				close(pipe_fd[j]);
				j++;
			}
			close(fd_out);  // Close the output file descriptor in child
			
			execute_cmd(cmd[i], envp); // Execute the command
			exit(1);
		}
		i++;
	}
	i = 0;
	// Close all pipe file descriptors in the parent
	while (i < 2 * (num_cmd - 1))
	{
		close(pipe_fd[i]);
		i++;
	}
	close(fd_out);  // Close the output file descriptor in parent
	free(pipe_fd);
	i = 0;
	while (i < num_cmd) // Wait for all child processes to finish
	{
		wait(NULL);
		i++;
	}
}*/

/* Learning to emulate the "|" operator 
int	main(int argc, char **argv, char **envp)
{
	char	*argumentos[] = {"ping", "-c", "5", "google.com", NULL};
	char	*argumentosfinais[] = {"grep", "rtt", NULL};
	int		fd[2];
	int		pid1;
	int		pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
	{
		// ping
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_cmd(argumentos, envp);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (3);
	if (pid2 == 0)
	{
		// grep
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_cmd(argumentosfinais, envp);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}*/

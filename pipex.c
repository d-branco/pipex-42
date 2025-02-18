/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:12:30 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/27 19:47:18 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//static int	check_argument_bonus(int argc, char **envp);
static int	check_argument(int argc, char **envp);
//static void	deliverance_input_visualization(int argc, char **argv);
static int	first_command(char **argv, char **envp, int *pipe_fd);
static void	last_command(char **argv, char **envp, int *pipe_fd);

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	process_id;

	if (check_argument(argc, envp) != 0)
		return (1);
	if (pipe(pipe_fd) == -1)
		return (perror(NULL), 2);
	process_id = fork();
	if (process_id == -1)
		return (perror(NULL), 3);
	if (process_id == 0)
		if (first_command(argv, envp, pipe_fd) != 0)
			return (4);
	waitpid (0, NULL, 0);
	last_command(argv, envp, pipe_fd);
}

static int	first_command(char **argv, char **envp, int *pipe_fd)
{
	int		infile_fd;
	char	**command;

	infile_fd = open(argv[1], O_RDONLY, 0644);
	if (infile_fd == -1)
	{
		perror(NULL);
		return (1);
	}
	close(pipe_fd[0]);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	command = ft_split(argv[2], ' ');
	if (!command)
		return (2);
	execute_cmd(command, envp);
	free_splitted_str(command);
	close(infile_fd);
	return (3);
}

// PIPE read	0
// PIPE write	1
//	0	Standard INPUT
//	1	Standard OUTPUT
//	2	Standard error
static void	last_command(char **argv, char **envp, int *pipe_fd)
{
	int		outfile_fd;
	char	**command;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile_fd == -1)
	{
		perror(NULL);
		return ;
	}
	close(pipe_fd[1]);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	command = ft_split(argv[3], ' ');
	if (!command)
		return ;
	execute_cmd(command, envp);
	free_splitted_str(command);
	close(outfile_fd);
	exit(1);
}

/*
static void	deliverance_input_visualization(int argc, char **argv)
{
	int	i_deliverance;

	ft_printf("Input interpretation:\n< %s %s", argv[1], argv[2]);
	i_deliverance = 3;
	while (i_deliverance < argc - 1)
	{
		ft_printf(" | %s ", argv[i_deliverance]);
		i_deliverance++;
	}
	ft_printf("> %s\n\n", argv[argc - 1]);
}
*/

static int	check_argument(int argc, char **envp)
{
	int	result;

	result = 0;
	if (!envp)
		result = 3;
	if (argc < 4 + 1)
	{
		write(1, &"Too few arguments!\n", 19);
		write(1, &"usage:    $ ./pipex file1 cmd1 cmd2 file2\n", 42);
		result = 1;
	}
	if (argc > 4 + 1)
	{
		write(1, &"Too many arguments!\n", 20);
		write(1, &"usage:    $ ./pipex file1 cmd1 cmd2 file2\n", 42);
		result = 2;
	}
	return (result);
}

/*
static int	check_argument_bonus(int argc, char **envp)
{
	int	result;

	result = 0;
	if (!envp)
		result = 3;
	if (argc < 4 + 1)
	{
		write(1, &"Too few arguments!\n", 19);
		write(1, &"usage:    $ ./pipex file1 cmd1 cmd2 file2\n", 42);
		result = 1;
	}
	return (result);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pipex_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:15:46 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/05 22:35:54 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_pipex_bonus.h"

void	free_splitted_str(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_path_from_envp(char **cmd_args, char **envp)
{
	char	**path_splitted;
	char	*path;
	char	*path2;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	path_splitted = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_splitted[i])
	{
		path = ft_strjoin(path_splitted[i], "/");
		path2 = ft_strjoin(path, cmd_args[0]);
		free(path);
		if (access(path2, X_OK) == 0)
		{
			free_splitted_str(path_splitted);
			return (path2);
		}
		free(path2);
		i++;
	}
	free_splitted_str(path_splitted);
	return (NULL);
}

void	execute_cmd(char **cmd_args, char **envp)
{
	char	*cmd_with_path;

	if (cmd_args[0][0] == '/')
	{
		execve(cmd_args[0], cmd_args, NULL);
	}
	else
	{
		cmd_with_path = find_path_from_envp(cmd_args, envp);
		if (cmd_with_path == NULL)
			return ;
		execve(cmd_with_path, cmd_args, NULL);
	}
	perror(NULL);
	free_splitted_str(cmd_args);
}

void	here_doc_put_in(char **argv, int *pipe_fd)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
}

void	here_doc_initialize(char **argv)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		wait(NULL);
	}
	else
		here_doc_put_in(argv, pipe_fd);
}

void	piping(char **cmd, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		execute_cmd(cmd, envp);
	}
}

static int	check_argument(int argc, char **argv, char **envp)
{
	int	result;

	result = 0;
	if (!envp)
		result = 3;
	if (argc < 4 + 1)
	{
		write(2, &"Too few arguments!\n", 19);
		write(2, &"usage:    $ ./pipex file1 cmd1 cmd2 file2\n", 42);
		result = 1;
	}
	else if ((argc < 5 + 1) && (ft_strncmp(argv[1], "here_doc", 9) == 0))
	{
		write(2, &"Too few arguments!\n", 19);
		write(2, &"usage:    $ ./pipex here_doc LIMITER cmd cmd1 file\n", 42);
		result = 2;
	}
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	int	step;
	int	input_fd;
	int	output_fd;

	if (check_argument(argc, argv, envp) != 0)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (output_fd == -1)
			perror("");
		here_doc_initialize(argv);
		step = 3;
	}
	else
	{
		input_fd = open(argv[1], O_RDONLY, 0777);
		if (input_fd == -1)
			perror("");
		output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (output_fd == -1)
			perror("");
		dup2(input_fd, 0);
		step = 2;
	}
	while (step < argc - 2)
	{
		piping(ft_split(argv[step], ' '), envp);
		step++;
	}
	dup2(output_fd, 1);
	execute_cmd(ft_split(argv[argc - 2], ' '), envp);
}

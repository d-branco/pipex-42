/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:15:46 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/13 09:46:56 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	piping(char **cmd, char **envp);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-piping2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:09:39 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/21 10:28:17 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_children(int num_cmd)
{
	int	i;

	i = 0;
	while (i < num_cmd)
	{
		wait(NULL);
		i++;
	}
}

void	redirect_child(int i, int num_cmd, int *pipe_fd, int fd_out)
{
	if (i > 0)
	{
		if (dup2(pipe_fd[2 * (i - 1)], STDIN_FILENO) == -1)
			handle_error("dup2 failed", fd_out);
	}
	if (i < num_cmd - 1)
	{
		if (dup2(pipe_fd[2 * i + 1], STDOUT_FILENO) == -1)
			handle_error("dup2 failed", fd_out);
	}
	else
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			handle_error("dup2 failed", fd_out);
	}
}

void	handle_error(char *message, int fd_out)
{
	perror(message);
	if (fd_out != -1)
		close(fd_out);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:00:50 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/15 09:00:50 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./ft_printf/ft_printf.h"

# include <unistd.h> //	close(), read(), write(),
//	access(), dup(), dup2(), execve(), fork(), pipe(), unlink()
# include <stdlib.h> //	malloc(), free(), exit()
# include <stdio.h> //	perror()
//# include <string.h> //	strerror()
# include <sys/wait.h> //	wait(), waitpid()
# include <fcntl.h> //open()

void	execute_cmd(char **cmd_args, char **envp);
void	free_splitted_str(char **str);
void	execute_pipeline(char ***cmd, int num_cmd, char **envp, char *outfile);

void	handle_error(char *message, int fd_out);
void	redirect_child(int i, int num_cmd, int *pipe_fd, int fd_out);
void	wait_for_children(int num_cmd);

#endif
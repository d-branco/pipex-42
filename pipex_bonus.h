/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:16:21 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/13 09:45:28 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"

# include <unistd.h> //	close(), read(), write(),
//	access(), dup(), dup2(), execve(), fork(), pipe(), unlink()
# include <stdlib.h> //	malloc(), free(), exit()
# include <stdio.h> //	perror()
//# include <string.h> //	strerror()
# include <sys/wait.h> //	wait(), waitpid()
# include <fcntl.h> //open()

//pipex_bonus.c
//pipex-utils_bonus.c
int		check_argument(int argc, char **argv, char **envp);
void	free_splitted_str(char **arr);
//pipex-here_doc_bonus.c
void	here_doc_get_next_line(char **argv, int *pipe_fd);
void	here_doc_initialize(char **argv);
//pipex-exec_bonus.c
char	*find_path_from_envp(char **cmd_args, char **envp);
void	execute_cmd(char **cmd_args, char **envp);

#endif

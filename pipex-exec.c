/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:54:14 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/18 10:44:04 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	usage
cc test.c -o test && ./test; rm test
*/

static char	*find_path_from_envp(char **cmd_args, char **envp);
static void	free_splitted_str(char **str);

void	execute_cmd(char **cmd_args, char **envp)
{
	int		id;
	char	*cmd_with_path;

	id = fork();
	if (id == 0)
	{
		if (cmd_args[0][0] == '/')
		{
			execve(cmd_args[0], cmd_args, NULL);
			perror("");
		}
		else
		{
			cmd_with_path = find_path_from_envp(cmd_args, envp);
			execve(cmd_with_path, cmd_args, NULL);
			perror("");
		}
	}
	else if (id == -1)
		perror("Forking error.\n");
	else
		wait(NULL);
}

static char	*find_path_from_envp(char **cmd_args, char **envp)
{
	char	**path_splitted;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	path_splitted = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_splitted[i])
	{
		path = ft_strjoin(path_splitted[i], "/");
		path = ft_strjoin(path, cmd_args[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_splitted_str(path_splitted);
			return (path);
		}
		free(path);
		i++;
	}
	free_splitted_str(path_splitted);
	return (NULL);
}

static void	free_splitted_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

/*	clear; cc pipex-exec.c ./ft_printf/libftprintf.a && valgrind ./a.out
int	main(int argc, char** argv, char **envp)
{
	char	*cmd_args[] = {"echo", "echo", "Funciona", NULL};

	execute_cmd(cmd_args, envp);
}*/

/*int	main(int argc, char **argv) //communicating with fork and pipe
{
	int	fd[2];
	int	id;
	int	x;
	int	y;

	if (pipe(fd) ==- 1)
	{
		perror("An error occured opening the pipe\n");
		return (1);
	}
	if((id = fork()) == -1)
		return (3);
	if (id == 0) // in the child process
	{
		close(fd[0]);
		printf("Insere um numero: ");
		scanf("%d", &x);
		if ((write(fd[1], &x, sizeof(int))) == -1)
		{
			printf("Erro em write()\n");
			return (2);
		}
		close(fd[1]);
	}
	else // in the parent process
	{
		close(fd[1]);
		if ((read(fd[0], &y, sizeof(int))) == -1)
		{
			printf("Erro em read()\n");
			return (1);
		}
		y = y * 3;
		close(fd[0]);
		printf("Obteve-se do child: %d\n", y);
	}

	return (0);
}*/

/*	LIMPA O TERMINAL
static int	ad_clear_terminal(void);

int	main(void)
{
	if (ad_clear_terminal())
		return (1);
}

static int	ad_clear_terminal(void)
{
	char	*clear_argv[2];
	char	*envp[2];

	envp[0] = "TERM=xterm";
	envp[1] = NULL;
	clear_argv[0] = "clear";
	clear_argv[1] = NULL;
	execve("/usr/bin/clear", clear_argv, envp);
	return (1);
}
*/

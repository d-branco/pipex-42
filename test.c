/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:54:14 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/17 10:50:07 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	usage
cc test.c -o test && ./test; rm test
*/

void	execute_cmd(char **cmd_args);

int	main(void)
{
	char *argumentos[] = {"/bin/ls", "-l", NULL};

	execute_cmd(argumentos);
}

void	execute_cmd(char **cmd_args)
{
	execve(cmd_args[0], cmd_args, NULL);
	perror("");
}


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
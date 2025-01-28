/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:54:14 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/27 17:47:47 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	usage
cc test.c -o test && ./test; rm test
*/

static char	*find_path_from_envp(char **cmd_args, char **envp);
void		free_splitted_str(char **str);

/* to debugg
		ft_putstr_fd(cmd_with_path, 2);
		ft_putstr_fd(":\n", 2);
copy before the execve()	*/
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
		free(cmd_with_path);
	}
	perror(NULL);
	free_splitted_str(cmd_args);
}
/*void	execute_cmd(char **cmd_args, char **envp)
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
		waitpid(id, NULL, 0);
		free(cmd_with_path);
}*/

static char	*find_path_from_envp(char **cmd_args, char **envp)
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

void	free_splitted_str(char **str)
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

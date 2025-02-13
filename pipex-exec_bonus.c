/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:44:14 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/13 09:44:32 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

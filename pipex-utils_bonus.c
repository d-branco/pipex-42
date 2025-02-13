/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-initialize_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:23:37 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/13 09:40:57 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_argument(int argc, char **argv, char **envp)
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

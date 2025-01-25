/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:12:30 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/25 14:59:09 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//static int	check_argument(int argc, char **argv);
static int	check_argument_bonus(int argc);
static void	deliverance_input_visualization(int argc, char **argv);
char		**first_command(char **argv);
char		**last_command(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	***commands;
	int		infile;

	if (check_argument_bonus(argc) != 0)
		return (1);
	deliverance_input_visualization(argc, argv);
	infile = open("l.txt", O_RDONLY, 0644);
	if (infile == -1)
		return (perror(NULL), 3);
	dup2(infile, STDIN_FILENO);
	commands = malloc((argc - 3) * sizeof(char **));
	commands[0] = first_command(argv);
	i = 1;
	while (i < argc - 4)
	{
		commands[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	commands[i] = last_command(argc, argv);

	ft_printf("Inputs:\n");
	i = 0;
	while(i < argc - 3)
	{
		int j = 0;
		ft_printf("    ");
		while (commands[i][j])
		{
			ft_printf("%s, ", commands[i][j]);
			j++;
		}
		ft_printf("%s\n", commands[i][j]);
		i++;
	}
	ft_printf("\n");
	
	execute_pipeline(commands, argc - 3, envp, argv[argc - 1]);
	i = 0;
	while (i < argc - 3)
	{
		free_splitted_str(commands[i]);
		i++;
	}
	free(commands);
}

char	**last_command(int argc, char **argv)
{
	char	**arguments;

	arguments = ft_split(argv[argc - 2], ' ');
	return (arguments);
	close(infile);
}

char	**first_command(char **argv)
{
	char	**arguments;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(" ");
	temp2 = ft_strjoin(argv[2], temp1);
	free(temp1);
	temp1 = ft_strjoin(temp2, argv[1]);
	free(temp2);
	arguments = ft_split(temp1, ' ');
	free(temp1);
	return (arguments);
}

static void	deliverance_input_visualization(int argc, char **argv)
{
	int	i_deliverance;

	ft_printf("Input interpretation:\n< %s %s ", argv[1], argv[2]);
	i_deliverance = 3;
	while (i_deliverance < argc - 1)
	{
		ft_printf(" | %s ", argv[i_deliverance]);
		i_deliverance++;
	}
	ft_printf("> %s\n\n", argv[argc - 1]);
}

/*
static int	check_argument(int argc, char **argv)
{
	int	result;

	result = 0;
	if (argc < 4 + 1)
	{
		write(1, &"Too few arguments!\n", 19);
		write(1, &"usage:    $ ./pipex file1 cmd1 cmd2 file2\n", 42);
		result = 1;
	}
	if (argc > 4 + 1)
	{
		write(1, &"Too many arguments!\n", 20);
		write(1, &"usage:    $ ./pipex file1 cmd1 cmd2 file2\n", 42);
		result = 2;
	}
	return (result);
}
*/

static int	check_argument_bonus(int argc)
{
	int	result;

	result = 0;
	if (argc < 4 + 1)
	{
		write(1, &"Too few arguments!\n", 19);
		write(1, &"usage:    $ ./pipex file1 cmd1 cmd2 file2\n", 42);
		result = 1;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:54:14 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/15 10:33:54 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
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

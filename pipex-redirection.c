/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:08:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/19 09:51:27 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*		Redirectors
<	Input redirection
		- takes input from a file
		e. g.: 
			- command < input.txt
			- < input.txt | command
<<	Here Document
		- provies multiple lines of input in the C.L.I.
		e. g.: 
			- command <<DELIMITER
			- cat << EOF (enter)
				-texto
				texto EOF (the DELIMITER only works on the start of the line)
				EOF (enter to finihsi)
together:
	- cat > output.txt <<END

> Output redirection
>> Append to file */

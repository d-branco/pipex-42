/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:03:20 by abessa-m          #+#    #+#             */
/*   Updated: 2024/11/06 10:35:23 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	Function name
//		ft_split
//	Prototype
//		char **ft_split(char const *s, char c);
//	Turn in files
//		-
//	Parameters
//		s: The string to be split.
//		c: The delimiter character.
//	Return value
//		The array of new strings resulting from the split.
//		NULL if the allocation fails.
//	External functs.
//		malloc, free
//	Description
//		Allocates (with malloc(3)) and returns an array
//		of strings obtained by splitting ’s’ using the
//		character ’c’ as a delimiter. The array must end
//		with a NULL pointer.

#include "libft.h"
//	size_t, ft_substr(), NULL
//	char	*ft_substr(char const *s, unsigned int start, size_t len)

static char		*add_substring(char const *s, unsigned int start, char c);
static size_t	count_words(char const *s, char c);
static void		free_array(char **arr, size_t size);
char			**initialize_array(char const *s, char c,
					unsigned int *index_ptr);

char	**ft_split(char const *s, char c)
{
	char			**ptr;
	unsigned int	index;
	unsigned int	index_ptr;

	ptr = initialize_array(s, c, &index_ptr);
	if (!ptr)
		return (NULL);
	index = 1;
	while ((s[index] != '\0') && (c != '\0'))
	{
		if ((s[index - 1] == c && s[index] != c))
		{
			ptr[index_ptr] = add_substring(s, index, c);
			if (ptr[index_ptr] == NULL)
			{
				free_array(ptr, index_ptr);
				return (NULL);
			}
			index_ptr++;
		}
		index++;
	}
	ptr[index_ptr] = NULL;
	return (ptr);
}

char	**initialize_array(char const *s, char c, unsigned int *index_ptr)
{
	char			**ptr;
	unsigned int	count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ptr)
		return (NULL);
	*index_ptr = 0;
	if (s[0] != c && s[0] != '\0')
	{
		ptr[*index_ptr] = add_substring(s, 0, c);
		if (ptr[*index_ptr] == NULL)
		{
			free_array(ptr, *index_ptr);
			return (NULL);
		}
		(*index_ptr)++;
	}
	return (ptr);
}

static char	*add_substring(char const *s, unsigned int start, char c)
{
	size_t	len;

	len = 0;
	while (s[len + start] != c && s[len + start] != '\0')
		len++;
	return (ft_substr(s, start, len));
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	j;

	if (s[0] == '\0')
		return (0);
	count = 0;
	if (s[0] != c)
		count = 1;
	j = 1;
	while (s[j] != '\0')
	{
		if (s[j] == c && s[j + 1] != '\0' && s[j + 1] != c)
			count++;
		j++;
	}
	return (count);
}

static void	free_array(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

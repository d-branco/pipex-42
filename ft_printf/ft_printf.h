/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:03:01 by abessa-m          #+#    #+#             */
/*   Updated: 2025/01/09 14:55:51 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *initial_str, ...);
void	printf_integer(char *conv_str, int *count, va_list ptr_args);
void	printf_character(char *conv_str, int *count, va_list ptr_args);
void	printf_string(char *conv_str, int *count, va_list ptr_args);
void	printf_unsigned_integer(char *conv_str, int *count, va_list ptr_args);
void	printf_unsigned_d(char *conv_str, int *count, va_list ptr_args);
char	*ft_ultoa(unsigned long nbr, unsigned int radix);
void	printf_hex_lower(char *conv_str, int *count, va_list ptr_args);
void	printf_hex_upper(char *conv_str, int *count, va_list ptr_args);
void	printf_pointer(char *conv_str, int *count, va_list ptr_args);
void	ft_format_alternate(char *conv_str, char **str);
size_t	ft_format_width(char *conv_str, char **str);
void	ft_format_precision_string(char *conv_str, char **str);
void	ft_format_precision_numeric(char *conv_str, char **str);
void	ft_format_precision_hexadecimal(char *conv_str, char **str);
int		ft_hextoi(char *hex_str);
char	ft_format_place_sign(char *conv_str, char **str);

#endif

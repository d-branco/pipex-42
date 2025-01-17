# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 17:56:00 by abessa-m          #+#    #+#              #
#    Updated: 2025/01/17 11:12:15 by abessa-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
LIBFT	= libft/libft.a
########################################################### Compiler and Flags #
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
####################################################################### Remove #
RM		= rm -f
###################################################################### Arquive #
AR		= ar rcs
###################################################################### Sources #
SRCS	=	\
			ft_printf.c ft_printf-conversion-precision.c \
			ft_printf-decimal.c ft_printf-hex.c \
			ft_printf-conversion.c ft_printf-conversion-numeric.c \
			ft_printf-conversion-sign.c 
OBJS	= $(SRCS:.c=.o)

SRCS-BONUS	=	\
			ft_printf_bonus.c ft_printf-conversion-precision_bonus.c \
			ft_printf-decimal_bonus.c ft_printf-hex_bonus.c \
			ft_printf-conversion_bonus.c ft_printf-conversion-numeric_bonus.c \
			ft_printf-conversion-sign_bonus.c 
OBJS-BONUS	= $(SRCS-BONUS:.c=.o)
###################################################################### Headers #
HEADERS	= ft_printf.h
############################################################ Mandatory Targets #
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@cd libft \
	&& ar x libft.a \
	&& cd .. \
	&& $(AR) $(NAME) libft/*.o $(OBJS) \

#	&& echo "$(PURPLE)Library built: $(NAME)$(COR)"

%.o: %.c ft_printf.h
	@$(CC) $(CFLAGS) -c $< -o $@ \

#	&& echo "$(GRAY)compiled: $(COR) $<: "

clean:
	@make --no-print-directory -C libft clean \
	&& $(RM) $(OBJS) $(OBJS-BONUS) \

#	&& echo "$(GRAY)Objects removed$(COR)"

fclean: clean
	@make --no-print-directory -C libft fclean \
	&& $(RM) $(NAME) \

#	&& echo "$(GRAY)Libraries removed$(COR)"

re: fclean all
	@echo "$(GRAY)redone$(COR)"

.PHONY: all clean fclean re
################################################################ Bonus Targets #
bonus: $(OBJS-BONUS) $(LIBFT)
	@cd libft \
	&& ar x libft.a \
	&& cd .. \
	&& $(AR) $(NAME) libft/*.o $(OBJS-BONUS) \
	&& echo "$(PURPLE)Library built: $(NAME)$(COR)"
################################################################## Build libft #
$(LIBFT):
	@make --no-print-directory -C libft \

#	&& echo "$(PURPLE)Library built: $(LIBFT)$(COR)"
###################################################################### Colors  #
# COlor Remove
COR = \033[0m    
# purple
PURPLE = \033[1;35m    
# gray
GRAY = \033[1;90m    
# yellow
YELLOW = \033[1;93m    

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 10:43:59 by abessa-m          #+#    #+#              #
#    Updated: 2025/01/27 19:46:35 by abessa-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex
LIBFT		:= ./ft_printf/libftprintf.a
#################################################################### Compiler  #
CC			:= cc
CFLAGS		:= -g -Wall -Werror -Wextra
########################################################## Intermidiate steps  #
RM			:= rm -f
AR			:= ar rcs
######################################################### Objects and Headers  #
SRCS		= pipex.c pipex-exec.c
OBJS		= $(SRCS:.c=.o)
HEADERS		= pipex.h
##################################################################### Targets  #
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME) \
	&& echo "$(GRAY)Compiled:$(COR) $(SRCS)"

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ \

$(LIBFT):
	@make --no-print-directory -C ft_printf \
	&& echo "$(PURPLE)Library built: $(LIBFT)$(COR)"

bonus: $(LIBFT)

clean:
	@$(RM) *.o *.gch ; \
	make --no-print-directory -C ft_printf clean \

fclean: clean
	@@make --no-print-directory -C ft_printf fclean \
	&& $(RM) $(NAME) \
	&& echo "$(GRAY)$(NAME) removed$(COR)"

re: fclean all	
	@echo "$(GRAY)redone$(COR)"
####################################################################### Colors #
COR = \033[0m		# COlor Remove
PURPLE = \033[1;35m	# purple
GRAY = \033[1;90m	# gray
YELLOW = \033[1;93m	# yellow
######################################################################## Test  #
test: re
	@echo -n "$(YELLOW)" ; \
	norminette *.c | grep -v -E \
	"25 lines|Comment is invalid in this scope" \
	| grep Error ; echo -n "$(COR)\n" ; \
	valgrind --quiet --show-error-list=yes --track-fds=all \
	./pipex infile "cat -e" "grep 42" outfile; \
	echo "\nReturn value: $$?" ; \
	$(RM) *.o *.gch ; \
	make --no-print-directory -C ft_printf clean ; \
	echo "\ncat outfile:"; cat outfile

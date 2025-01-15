# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 10:43:59 by abessa-m          #+#    #+#              #
#    Updated: 2025/01/15 16:52:33 by abessa-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

test:
	@echo -n "$(YELLOW)" ; \
	norminette *.c | grep -v -E \
	"25 lines|Comment is invalid in this scope|Too many variables declarations in a function" \
	| grep Error: ; echo -n "$(COR)\n" ; \
	cc pipex.c \
	&&./a.out infile "grep a1" "grep a" "grep 1" "wc -w" outfile; \
	echo "\nReturn value: $$?"

NAME	:= pipex
#################################################################### Compiler  #
CC		:= cc
CFLAGS	:= -g \
#-Wall -Werror -Wextra
########################################################## Intermidiate steps  #
RM		:= rm -f
AR		:= ar rcs
##################################################################### Targets  #
all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) pipex.c -o $(NAME) \
	&& echo "$(GRAY)Compiled:$(COR) $(NAME)"

bonus:

clean:

fclean: clean
	@$(RM) $(NAME) \
	&& echo "$(GRAY)$(NAME) removed$(COR)"

re: fclean all
	@echo "$(GRAY)redone$(COR)"
###################################################################### Colors  #
# COlor Remove
COR = \033[0m
# purple
PURPLE = \033[1;35m
# gray
GRAY = \033[1;90m
# yellow
YELLOW = \033[1;93m
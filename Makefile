# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 10:43:59 by abessa-m          #+#    #+#              #
#    Updated: 2025/02/05 22:22:22 by abessa-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex
LIBFT		:= ./$(LIBFT-DIR)/libft.a
LIBFT-DIR	:= libft
#################################################################### Compiler  #
CC			:= cc
CFLAGS		:= -g -Wall -Werror -Wextra
########################################################## Intermidiate steps  #
RM			:= rm -f
AR			:= ar rcs
######################################################### Objects and Headers  #
SRCS		= pipex.c pipex-exec.c
OBJS		= $(SRCS:.c=.o)
SRCS-BONUS	= b_pipex_bonus.c 
OBJS-BONUS	= $(SRCS-BONUS:.c=.o)
HEADERS		= pipex.h b_pipex_bonus.h
##################################################################### Targets  #
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME) \
	&& echo "$(GRAY)Compiled:$(COR) $(SRCS)"

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ \

$(LIBFT):
	@make --no-print-directory -C $(LIBFT-DIR) \
	&& echo "$(PURPLE)Library built: $(LIBFT)$(COR)"

bonus: $(OBJS-BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SRCS-BONUS) $(LIBFT) -o $(NAME) \
	&& echo "$(GRAY)Compiled:$(COR) $(SRCS-BONUS)"

clean:
	@$(RM) *.o *.gch ; \
	make --no-print-directory -C $(LIBFT-DIR) clean \

fclean: clean
	@@make --no-print-directory -C $(LIBFT-DIR) fclean \
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
	make --no-print-directory -C $(LIBFT-DIR) clean ; \
	echo "\ncat outfile:"; cat outfile

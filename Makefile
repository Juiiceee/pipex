# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 15:57:01 by lbehr             #+#    #+#              #
#    Updated: 2024/02/13 12:21:11 by lbehr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex
OBJ_DIR		:= obj
SRCS		:= error.c ft_split.c main.c process.c utils.c utilsprocess.c
SRCS		:= $(SRCS:%=%)
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)
CC			:= cc
NORM		:= norminette *
CFLAGS		:= -Wall -Wextra -Werror -g3
RM			:= rm -rf
DIR_DUP		= mkdir -p $(@D)

all		: norm $(NAME)

norm	:
	$(NORM)

$(NAME)	:	$(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(DIR_DUP)
	$(CC) -c $< $(CFLAGS) -o $@

clean	:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY: all clean fclean re norm
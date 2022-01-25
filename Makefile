# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 14:37:51 by rpohlen           #+#    #+#              #
#    Updated: 2022/01/24 23:23:05 by rpohlen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAIN_SRV	= main_server.c

MAIN_CLI	= main_client.c

PRINTF		= $(addprefix src/printf/, \
			  ft_printf.c \
			  ft_printf_args.c \
			  ft_printf_args2.c \
			  ft_printf_flags.c \
			  ft_printf_output.c \
			  ft_printf_utils.c \
			  ft_printf_utils_list.c \
			  ft_printf_utils_list2.c)

UTIL		= $(addprefix src/util/, \
			  ft_atoi.c \
			  ft_isint.c)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude

NAME_S		= server

NAME_C		= client

OBJ			= $(PRINTF:.c=.o) $(UTIL:.c=.o)

OBJ_S		= $(MAIN_SRV:.c=.o) $(OBJ)

OBJ_C		= $(MAIN_CLI:.c=.o) $(OBJ)

all:		$(NAME_C) $(NAME_S)

$(NAME_S):	$(OBJ_S)
			$(CC) $(CFLAGS) $(OBJ_S) -o $(NAME_S)

$(NAME_C):	$(OBJ_C)
			$(CC) $(CFLAGS) $(OBJ_C) -o $(NAME_C)

clean:
			rm -rf $(OBJ_S) $(OBJ_C)

fclean:		clean
			rm -rf $(NAME_S) $(NAME_C)

re:			fclean all

.PHONY:		all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/13 13:12:36 by gcefalo           #+#    #+#              #
#    Updated: 2021/03/08 18:03:03 by gcefalo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

SRCS	= $(wildcard srcs/main.c) \
		  $(wildcard srcs/libft/*) \
		  $(wildcard srcs/math/*) \
		  $(wildcard srcs/read_input/*) \

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -I /usr/local/include -I ./include

LFLAGS	= -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

%.o :		%.c
			gcc -c $(CFLAGS) $< -o $@

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

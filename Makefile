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

SRCS	= srcs/main.c \
		  srcs/utils/ft_color.c \
		  srcs/utils/ft_strncmp.c \
		  srcs/utils/get_next_line.c \
		  srcs/utils/get_next_line_utils.c \
		  srcs/utils/mlx_utils.c \
		  srcs/math/ft_intersections.c \
		  srcs/math/ft_intersections_utils.c \
		  srcs/math/ft_vectors.c \
		  srcs/read_rt/append_to_list.c \
		  srcs/read_rt/append_to_list_2.c \
		  srcs/read_rt/create_elem.c \
		  srcs/read_rt/create_elem_2.c \
		  srcs/read_rt/create_elem_2_utils.c \
		  srcs/read_rt/ft_read.c \
		  srcs/read_rt/ft_read_2.c \
		  srcs/manage_scene/get_pixel_color.c \
		  srcs/manage_scene/manage_scene.c \
		  srcs/inputs/input_manager.c \
		  srcs/inputs/input_utils.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -I ./mlx -I ./include

LFLAGS	= libmlx.dylib -L ./mlx -framework Metal -framework AppKit

%.o :		%.c
			gcc -c -g $(CFLAGS) $< -o $@

$(NAME):	$(OBJS)
			make -C mlx
			mv mlx/libmlx.dylib .
			gcc -g $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJS)
			rm -f libmlx.dylib

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

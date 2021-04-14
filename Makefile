NAME		= miniRT
BONUS_NAME	= miniRT_bonus

SRCS	= srcs/main.c \
		  srcs/utils/ft_color.c \
		  srcs/utils/ft_color_2.c \
		  srcs/utils/ft_strncmp.c \
		  srcs/utils/get_next_line.c \
		  srcs/utils/get_next_line_utils.c \
		  srcs/utils/mlx_utils.c \
		  srcs/utils/ft_memcpy.c \
		  srcs/utils/ft_bzero.c \
		  srcs/utils/free.c \
		  srcs/math/ft_intersections.c \
		  srcs/math/ft_intersections_utils.c \
		  srcs/math/ft_vectors.c \
		  srcs/math/ft_vectors_2.c \
		  srcs/math/ft_vectors_3.c \
		  srcs/read_rt/append_to_list.c \
		  srcs/read_rt/append_to_list_2.c \
		  srcs/read_rt/create_elem.c \
		  srcs/read_rt/create_elem_2.c \
		  srcs/read_rt/create_elem_2_utils.c \
		  srcs/read_rt/ft_read.c \
		  srcs/read_rt/ft_read_2.c \
		  srcs/manage_scene/get_pixel_color.c \
		  srcs/manage_scene/manage_scene.c \
		  srcs/manage_scene/aa_sampling.c \
		  srcs/inputs/input_manager.c \
		  srcs/inputs/input_utils.c \
		  srcs/inputs/transform_camera.c \
		  srcs/element_selection/select_sphere.c\
		  srcs/element_selection/select_light.c\
		  srcs/element_selection/select_triangle.c\
		  srcs/element_selection/select_square.c\
		  srcs/element_selection/select_square_utils.c\
		  srcs/element_selection/select_cylinder.c\
		  srcs/element_selection/select_plane.c\

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -I ./mlx -I ./include

LFLAGS	= libmlx.dylib -L ./mlx -framework Metal -framework AppKit

%.o :			%.c
				gcc -c -g $(CFLAGS) $< -o $@

$(NAME):		$(OBJS)
				make -C mlx
				mv mlx/libmlx.dylib .
				gcc -g $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(BONUS_NAME):	$(OBJS)
				make -C mlx
				mv mlx/libmlx.dylib .
				gcc -g $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME

all:			$(NAME)

bonus:			$(BONUS_NAME)

clean:
				rm -f $(OBJS)
				make clean -C mlx

fclean:			clean
				rm -f $(NAME)
				rm -f $(BONUS_NAME)
				rm -f libmlx.dylib
				rm -f screenshot.bmp

re:				fclean all

.PHONY:			all clean fclean re

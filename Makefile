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
		  srcs/inputs/input_manager.c \
		  srcs/inputs/input_utils.c \
		  srcs/inputs/transform_camera.c \
		  srcs/element_selection/select_sphere.c\
		  srcs/element_selection/select_light.c\
		  srcs/element_selection/select_triangle.c\
		  srcs/element_selection/select_square.c\
		  srcs/element_selection/select_cylinder.c\
		  srcs/element_selection/select_plane.c\

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -I /usr/local/include -I ./include

LFLAGS	= -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

%.o :		%.c
			gcc -c -g $(CFLAGS) $< -o $@

$(NAME):	$(OBJS)
			gcc -g $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

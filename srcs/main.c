#include "header.h"

void	init_scene(t_scene *scene)
{
	scene->w = 0;
	scene->h = 0;
	scene->mlx = 0;
	scene->win = 0;
	scene->amb_l.brightness = 0;
	scene->light = 0;
	scene->selected_light = 0;
	scene->cam = 0;
	scene->obj = 0;
	scene->selected_obj = 0;
}

void	read_input(t_scene *scene, char *file)
{
	int			fd;
	char		*line;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			add_element_to_scene(&line, scene);
	}
}

void	manage_scene(t_scene *scene)
{
	create_img(scene);
	mlx_key_hook(scene->win, keyboard_input, scene);
	mlx_mouse_hook(scene->win, mouse_input, scene);
	mlx_hook(scene->win, 17, 1L<<2, exit_func, NULL);
	main_info();
	mlx_loop(scene->mlx);
}

int		check_name(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] != 't' || s[i - 2] != 'r' || s[i - 3] != '.')
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene		scene;

	init_scene(&scene);
	srand(time(0));
	if (argc == 3 && check_name(argv[1]) && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		read_input(&scene, argv[1]);
		create_img(&scene);
		save_image_to_bmp_file(scene.img.img);
		printf(GRN"\tImage saved!\n\n");
		return (2);
	}
	else if (argc == 2 && check_name(argv[1]))
	{
		scene.mlx = mlx_init();
		read_input(&scene, argv[1]);
		scene.win = mlx_new_window(scene.mlx, scene.w, scene.h,
				"JohnnyBoy's miniRT");
		manage_scene(&scene);
	}
	else
	{
		//TODO error: "invalid input format"
	}
	return (1);
}

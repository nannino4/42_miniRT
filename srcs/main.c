#include "header.h"

void	init_scene(t_scene *scene)
{
	scene->w = 0;
	scene->h = 0;
	scene->mlx = 0;
	scene->win = 0;
	scene->amb_l.brightness = 0;
	scene->light = 0;
	scene->cam = 0;
	scene->obj = 0;
}

void	add_element_to_scene(char **line, t_scene *scene)
{
	if (ft_strncmp(*line, "R", 1) == 0)
		create_res(line, scene);
	else if (ft_strncmp(*line, "A", 1) == 0)
		create_amb_l(line, scene);
	else if (ft_strncmp(*line, "pl", 2) == 0)
		create_plane(line, scene);
	else if (ft_strncmp(*line, "sp", 2) == 0)
		create_sph(line, scene);
	else if (ft_strncmp(*line, "sq", 2) == 0)
		create_square(line, scene);
	else if (ft_strncmp(*line, "cy", 2) == 0)
		create_cyl(line, scene);
	else if (ft_strncmp(*line, "tr", 2) == 0)
		create_triangle(line, scene);
	else if (ft_strncmp(*line, "c", 1) == 0)
		create_cam(line, scene);
	else if (ft_strncmp(*line, "l", 1) == 0)
		create_light(line, scene);
	else
	{
		//TODO error: "unrecognized element"
	}
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
    //mlx_loop_hook(scene->mlx, idle, scene);
	mlx_hook(scene->win, 17, 1L<<2, exit_func, NULL);
	main_info();
	mlx_loop(scene->mlx);
}

int	main(int argc, char **argv)
{
	t_scene		scene;

	init_scene(&scene);
	srand(time(0));
	if (argc == 3 && argv[1] && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		//TODO --save
	}
	else if (argc == 2 && argv[1])
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
	return (0);
}

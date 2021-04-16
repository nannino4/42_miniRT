#include "header.h"

void	init_scene(t_scene *scene)
{
	scene->w = -1;
	scene->h = -1;
	scene->mlx = 0;
	scene->win = 0;
	scene->threading = &create_img;
	scene->aa_func = &pixel_no_aa;
	scene->save = 0;
	scene->amb_l.brightness = -1;
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
	char		*tmp;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf(RED"Error\n%s\n"RESET, strerror(errno));
		exit_func(scene);
	}
	while (get_next_line(fd, &line) > 0)
	{
		tmp = line;
		if (*line)
			add_element_to_scene(&line, scene);
		if (tmp)
			free(tmp);
	}
	if (line)
		free(line);
}

void	manage_scene(t_scene *scene)
{
	printf(BYEL"Generating Scene...\n"RESET);
	if (scene->save)
	{
		create_img_threaded(scene);
		printf(BGRN"Image Saved at program binary location !\n"RESET);
	}
	else
		scene->threading(scene);
	mlx_key_hook(scene->win, keyboard_input, scene);
	mlx_mouse_hook(scene->win, mouse_input, scene);
	mlx_hook(scene->win, 17, 1L << 2, exit_func, scene);
	if (!scene->save)
	{
		main_info();
		mlx_loop(scene->mlx);
	}
}

int	check_flags(int argc, char **s, t_scene *scene)
{
	int	i;

	if (argc < 2)
		return (0);
	while (argc > 2)
	{
		if (!ft_strncmp(s[argc - 1], "--save", 7))
			scene->save = 1;
		else if (!ft_strncmp(s[argc - 1], "--aa", 5))
			scene->aa_func = &pixel_with_aa;
		else if (!ft_strncmp(s[argc - 1], "--threaded", 11))
			scene->threading = &create_img_threaded;
		else
			return (-1);
		argc--;
	}
	i = 0;
	while (s[1][i])
		i++;
	if (i < 4 || s[1][i - 1] != 't' || s[1][i - 2] != 'r' || s[1][i - 3] != '.')
	{
		printf(RED"Error\nScene file name is invalid\n"RESET);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	int			tmp;

	init_scene(&scene);
	tmp = check_flags(argc, argv, &scene);
	if (tmp)
	{
		scene.mlx = mlx_init();
		read_input(&scene, argv[1]);
		if (scene.w <= 0 || scene.h <= 0 || !scene.cam)
		{
			printf(RED"Error\nResolution and camera are needed\n"RESET);
			exit_func(&scene);
		}
		scene.win = mlx_new_window(scene.mlx, scene.w, scene.h,
				"miniRT");
		manage_scene(&scene);
	}
	else if (tmp == -1)
		printf(RED"Error\nInvalid arguments\n"RESET);
	exit_func(&scene);
	return (0);
}

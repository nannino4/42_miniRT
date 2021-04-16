#include "header.h"

void	max_res(t_scene *scene)
{
	int		screen_res[2];
	double	reduction;

	mlx_get_screen_size(scene->mlx, &screen_res[0], &screen_res[1]);
	if (scene->w > (int)screen_res[0])
	{
		reduction = (double)scene->w / (double)screen_res[0];
		scene->w = (int)screen_res[0];
		scene->h /= reduction;
	}
	if (scene->h > (int)screen_res[1])
	{
		reduction = (double)scene->h / (double)screen_res[1];
		scene->h = (int)screen_res[1];
		scene->w /= reduction;
	}
}

void	create_res(char **line, t_scene *scene)
{
	int		minus;

	(*line)++;
	skip_spaces(line, scene);
	scene->w = read_int(line, &minus, scene);
	skip_spaces(line, scene);
	scene->h = read_int(line, &minus, scene);
	max_res(scene);
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Resolution\n"RESET);
		exit_func(scene);
	}
	else if (scene->w < 0 || scene->h < 0)
	{
		printf(RED"Error\nInvalid Resolution values\n"RESET);
		exit_func(scene);
	}
}

void	create_amb_l(char **line, t_scene *scene)
{
	(*line)++;
	skip_spaces(line, scene);
	scene->amb_l.brightness = read_double(line, scene);
	skip_spaces(line, scene);
	scene->amb_l.color = read_color(line, scene);
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Ambient light\n"RESET);
		exit_func(scene);
	}
	else if (scene->amb_l.brightness < 0)
	{
		printf(RED"Error\nInvalid Ambient light value \n"RESET);
		exit_func(scene);
	}
}

void	create_cam(char **line, t_scene *scene)
{
	t_cam	*cam;
	int		minus;

	(*line)++;
	cam = malloc(sizeof(t_cam));
	skip_spaces(line, scene);
	cam->origin = read_p(line, scene);
	skip_spaces(line, scene);
	cam->direction = read_norm_v(line, scene);
	skip_spaces(line, scene);
	cam->fov = read_int(line, &minus, scene);
	cam->next = 0;
	set_camera_orientation(cam);
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Camera values\n"RESET);
		exit_func(scene);
	}
	else if (cam->fov < 0 || cam->fov > 179)
	{
		printf(RED"Error\nInvalid Camera FOV value\n"RESET);
		exit_func(scene);
	}
	append_cam(scene, cam);
}

void	create_light(char **line, t_scene *scene)
{
	t_light		*light;

	(*line)++;
	light = malloc(sizeof(t_light));
	skip_spaces(line, scene);
	light->origin = read_p(line, scene);
	skip_spaces(line, scene);
	light->brightness = read_double(line, scene);
	skip_spaces(line, scene);
	light->color = read_color(line, scene);
	light->next = 0;
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Light values\n"RESET);
		exit_func(scene);
	}
	else if (light->brightness < 0 || light->brightness > 1)
	{
		printf(RED"Error\nInvalid Light Brightness values\n"RESET);
		exit_func(scene);
	}
	append_light(scene, light);
}

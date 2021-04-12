#include "header.h"
/*
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
*/
void	create_res(char **line, t_scene *scene)
{
	int		minus;

	(*line)++;
	skip_spaces(line);
	scene->w = read_int(line, &minus);
	skip_spaces(line);
	scene->h = read_int(line, &minus);
	if (scene->w > MAX_W)
		scene->w = MAX_W;
	if (scene->h > MAX_H)
		scene->h = MAX_H;
//	max_res(scene);
	if (**line || scene->w < 0 || scene->h < 0)
	{
		//TODO error: "resolution format is incorrect"
	}
}

void	create_amb_l(char **line, t_scene *scene)
{
	(*line)++;
	skip_spaces(line);
	scene->amb_l.brightness = read_double(line);
	skip_spaces(line);
	scene->amb_l.color = read_color(line);
	if (**line || scene->amb_l.brightness < 0)
	{
		//TODO error: "ambient light format is incorrect"
	}
}

void	create_cam(char **line, t_scene *scene)
{
	t_cam	*cam;
	int		minus;

	(*line)++;
	cam = malloc(sizeof(t_cam));
	skip_spaces(line);
	cam->origin = read_p(line);
	skip_spaces(line);
	cam->direction = read_norm_v(line);
	skip_spaces(line);
	cam->fov = read_int(line, &minus);
	cam->next = 0;
	set_camera_orientation(cam);
	if (**line || cam->fov < 0)
	{
		//TODO error: "camera format is incorrect"
	}
	append_cam(scene, cam);
}

void	create_light(char **line, t_scene *scene)
{
	t_light		*light;

	(*line)++;
	light = malloc(sizeof(t_light));
	skip_spaces(line);
	light->origin = read_p(line);
	skip_spaces(line);
	light->brightness = read_double(line);
	skip_spaces(line);
	light->color = read_color(line);
	light->next = 0;
	if (**line || light->brightness < 0 || light->brightness > 1)
	{
		//TODO error: "light format is incorrect"
	}
	append_light(scene, light);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:00:14 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/08 13:31:32 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_res(char **line, t_scene *scene)
{
	(*line)++;
	skip_spaces(line);
	scene->w = read_int(line);
	skip_spaces(line);
	scene->h = read_int(line);
	if (scene->w > MAX_W)
		scene->w = MAX_W;
	if (scene->h > MAX_H)
		scene->h = MAX_H;
	if (**line || scene->w < 0 || scene->h < 0)
	{
		//TODO error: "resolution format is incorrect"
	}
}

void	create_amb_l(char **line, t_scene *scene)
{
	t_amb_l		*new_amb_l;

	(*line)++;
	if ((new_amb_l = malloc(sizeof(t_amb_l))) == 0)
	{
		//TODO error: "allocazione di amb_l fallita"
	}
	skip_spaces(line);
	new_amb_l->brightness = read_double(line);
	skip_spaces(line);
	new_amb_l->color = read_color(line);
	if (**line || new_amb_l->brightness < 0)
	{
		//TODO error: "ambient light format is incorrect"
	}
	scene->amb_l = new_amb_l;
}


void	create_cam(char **line, t_scene *scene)
{
	t_cam	*cam;

	(*line)++;
	if ((cam = malloc(sizeof(t_cam))) == 0)
	{
		//TODO error: "allocazione di t_cam fallita"
	}
	skip_spaces(line);
	cam->origin = read_p(line);
	skip_spaces(line);
	cam->direction = read_norm_v(line);
	skip_spaces(line);
	cam->fov = read_int(line);
	cam->next = 0;
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
	if ((light = malloc(sizeof(t_light))) == 0)
	{
		//TODO error: "allocazione di t_light fallita"
	}
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

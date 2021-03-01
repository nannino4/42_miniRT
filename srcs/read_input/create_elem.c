/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:00:14 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/01 16:01:11 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_res(char **line, t_scene *scene, t_data *data)
{
	(*line)++;
	skip_spaces(line);
	data->w = read_int(line);
	skip_spaces(line);
	data->h = read_int(line);
	if (**line || data->w < 0 || data->h < 0)
	{
		//TODO error: "resolution format is incorrect"
	}
}

void	create_amb_l(char **line, t_scene *scene)
{
	t_amb_l		*amb_l;

	(*line)++;
	if ((amb_l = malloc(sizeof(t_amb_l))) == 0)
	{
		//TODO error: "allocazione di amb_l fallita"
	}
	skip_spaces(line);
	amb_l->t = read_double(line);
	skip_spaces(line);
	amb_l->trgb = read_color(line);
	if (**line || amb_l->t < 0)
	{
		//TODO error: "ambient light format is incorrect"
	}
	//TODO add amb_l to scene
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
	cam->p0 = read_p(line);
	skip_spaces(line);
	cam->v = read_norm_v(line);
	skip_spaces(line);
	cam->fov = read_int(line);
	if (**line || cam->fov < 0)
	{
		//TODO error: "camera format is incorrect"
	}
	//TODO add cam to scene
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
	light->p = read_p(line);
	skip_spaces(line);
	light->t = read_double(line);
	skip_spaces(line);
	light->trgb = read_color(line);
	if (**line || light->t < 0 || light->t > 1)
	{
		//TODO error: "light format is incorrect"
	}
	//TODO add light to scene
}

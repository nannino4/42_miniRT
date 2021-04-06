/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:21:08 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/06 16:56:48 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_obj(t_scene *scene)
{
	t_obj	*element;
	t_obj	*to_be_added;

	to_be_added = malloc(sizeof(t_obj));
	element = to_be_added;
	if (!scene->obj)
		scene->obj = to_be_added;
	else
	{
		element = scene->obj;
		while (element->next)
		{
			element = element->next;
		}
		element->next = to_be_added;
		element = element->next;
	}
	element->next = 0;
}

void	append_cam(t_scene *scene, t_cam *cam)
{
	t_cam	*element;

	element = scene->cam;
	if (!element)
	{
		scene->cam = cam;
		cam->prev = NULL;
	}
	else
	{
		while (element->next)
		{
			element = element->next;
		}
		cam->prev = element;
		element->next = cam;
	}
}

void	append_light(t_scene *scene, t_light *light)
{
	t_light	*element;

	element = scene->light;
	if (element)
	{
		while (element->next)
		{
			element = element->next;
		}
		element->next = light;
	}
	else
	{
		scene->light = light;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:21:08 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/08 17:37:00 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_obj(t_scene *scene)
{
	t_obj	*element;

	element = scene->obj;
	if (!element)
	{
		if (!(element = malloc(sizeof(t_obj))))
		{
			//TODO error: "allocation failed"
		}
	}
	else
	{
		while (element->next)
		{
			element = element->next;
		}
		if (!(element->next = malloc(sizeof(t_obj))))
		{
			//TODO error: "allocation failed"
		}
		element = element->next;
	}
	element->next = 0;
}

void	append_cam(t_scene *scene, t_cam *cam)
{
	t_cam	*element;

	element = scene->cam;
	if (element)
	{
		while (element->next)
		{
			element = element->next;
		}
		element->next = cam;
	}
	else
	{
		scene->cam = cam;
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

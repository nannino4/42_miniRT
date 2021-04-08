/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_list2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:04:39 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/06 16:57:16 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	append_sph(t_scene *scene, t_sph *sph)
{
	t_obj	*element;

	create_obj(scene);
	element = scene->obj;
	while (element->next)
		element = element->next;
	element->id = SPHERE;
	element->obj = (void *)sph;
}

void	append_plane(t_scene *scene, t_plane *plane)
{
	t_obj	*element;

	create_obj(scene);
	element = scene->obj;
	while (element->next)
		element = element->next;
	element->id = PLANE;
	element->obj = (void *)plane;
}

void	append_square(t_scene *scene, t_square *square)
{
	t_obj	*element;

	create_obj(scene);
	element = scene->obj;
	while (element->next)
		element = element->next;
	element->id = SQUARE;
	element->obj = (void *)square;
}

void	append_cyl(t_scene *scene, t_cyl *cyl)
{
	t_obj	*element;

	create_obj(scene);
	element = scene->obj;
	while (element->next)
		element = element->next;
	element->id = CYLINDER;
	element->obj = (void *)cyl;
}

void	append_triangle(t_scene *scene, t_triangle *triangle)
{
	t_obj	*element;

	create_obj(scene);
	element = scene->obj;
	while (element->next)
		element = element->next;
	element->id = TRIANGLE;
	element->obj = (void *)triangle;
}

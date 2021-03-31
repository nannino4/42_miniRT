/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:03:09 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/08 17:38:29 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_sph(char **line, t_scene *scene)
{
	t_sph		*sph;

	*line = *line + 2;
	if ((sph = malloc(sizeof(t_sph))) == 0)
	{
		//TODO error: "allocazione di t_sph fallita"
	}
	skip_spaces(line);
	sph->c = read_p(line);
	skip_spaces(line);
	sph->d = read_double(line);
	skip_spaces(line);
	sph->color = read_color(line);
	if (**line)
	{
		//TODO error: "shpere format is incorrect"
	}
	append_sph(scene, sph);
}

void	create_plane(char **line, t_scene *scene)
{
	t_plane		*plane;

	*line = *line + 2;
	if ((plane = malloc(sizeof(t_plane))) == 0)
	{
		//TODO error: "allocazione di t_plane fallita"
	}
	skip_spaces(line);
	plane->p0 = read_p(line);
	skip_spaces(line);
	plane->n = read_norm_v(line);
	skip_spaces(line);
	plane->color = read_color(line);
	if (**line)
	{
		//TODO error: "plane format is incorrect"
	}
	append_plane(scene, plane);
}

void	create_square(char **line, t_scene *scene)
{
	t_square		*square;

	*line = *line + 2;
	if ((square = malloc(sizeof(t_square))) == 0)
	{
		//TODO error: "allocazione di t_square fallita"
	}
	skip_spaces(line);
	square->c = read_p(line);
	skip_spaces(line);
	square->n = read_norm_v(line);
	skip_spaces(line);
	square->l = read_int(line);
	skip_spaces(line);
	square->color = read_color(line);
	set_square_orientation(square);
	if (**line)
	{
		//TODO error: "square format is incorrect"
	}
	append_square(scene, square);
}

void	create_cyl(char **line, t_scene *scene)
{
	t_cyl		*cyl;

	*line = *line + 2;
	if ((cyl = malloc(sizeof(t_cyl))) == 0)
	{
		//TODO error: "allocazione di t_cyl fallita"
	}
	skip_spaces(line);
	cyl->c = read_p(line);
	skip_spaces(line);
	cyl->n = read_norm_v(line);
	skip_spaces(line);
	cyl->d = read_int(line);
	skip_spaces(line);
	cyl->h = read_int(line);
	skip_spaces(line);
	cyl->color = read_color(line);
	set_cylinder_orientation(cyl);
	if (**line)
	{
		//TODO error: "cyl format is incorrect"
	}
	append_cyl(scene, cyl);
}

void	create_triangle(char **line, t_scene *scene)
{
	t_triangle		*triangle;

	*line = *line + 2;
	if ((triangle = malloc(sizeof(t_triangle))) == 0)
	{
		//TODO error: "allocazione di t_triangle fallita"
	}
	skip_spaces(line);
	triangle->p1 = read_p(line);
	skip_spaces(line);
	triangle->p2 = read_p(line);
	skip_spaces(line);
	triangle->p3 = read_p(line);
	skip_spaces(line);
	triangle->color = read_color(line);
	if (**line)
	{
		//TODO error: "triangle format is incorrect"
	}
	append_triangle(scene, triangle);
}

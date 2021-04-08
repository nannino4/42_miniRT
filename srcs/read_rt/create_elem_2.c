/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:03:09 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/06 17:00:44 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_sph(char **line, t_scene *scene)
{
	t_sph		*sph;

	*line = *line + 2;
	sph = malloc(sizeof(t_sph));
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
	plane = malloc(sizeof(t_plane));
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
	square = malloc(sizeof(t_square));
	skip_spaces(line);
	square->c = read_p(line);
	skip_spaces(line);
	square->n = read_norm_v(line);
	skip_spaces(line);
	square->l = read_double(line);
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
	cyl = malloc(sizeof(t_cyl));
	skip_spaces(line);
	cyl->c = read_p(line);
	skip_spaces(line);
	cyl->n = read_norm_v(line);
	skip_spaces(line);
	cyl->r = read_double(line) / 2.;
	skip_spaces(line);
	cyl->h = read_double(line) / 2.;
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
	triangle = malloc(sizeof(t_triangle));
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

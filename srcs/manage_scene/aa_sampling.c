/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_sampling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:29:52 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/14 15:37:27 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_sampling_points(t_sampling_points *p)
{
	p->dx[0] = 0.2;
	p->dx[1] = 0.2;
	p->dx[2] = 0.8;
	p->dx[3] = 0.8;
	p->dy[0] = 0.2;
	p->dy[1] = 0.8;
	p->dy[2] = 0.2;
	p->dy[3] = 0.8;
}

void	pixel_with_aa(t_scene *scene, int x, int y, t_color *final)
{
	int					i;
	t_ray				ray;
	t_sampling_points	p;
	t_color				reflection_color;

	i = 4;
	reflection_color = from_trgb_to_color(0);
	get_sampling_points(&p);
	while (i--)
	{
		create_ray(scene, &ray, x + p.dx[i], y + p.dy[i]);
		find_intersection(&ray, scene);
		if (ray.intersection.distance < MAX_DISTANCE)
			find_shadows(&ray, scene, &reflection_color);
		final->r += ray.intersection.obj_color.r * ray.light_color.r / 255;
		final->b += ray.intersection.obj_color.b * ray.light_color.b / 255;
		final->g += ray.intersection.obj_color.g * ray.light_color.g / 255;
	}
	*final = divide_color(*final, 4);
	reflection_color = divide_color(reflection_color, 4);
	mix_colors(final, reflection_color);
}

void	pixel_no_aa(t_scene *scene, int x, int y, t_color *final)
{
	t_ray	ray;
	t_color	reflection_color;

	reflection_color = from_trgb_to_color(0);
	create_ray(scene, &ray, x + 0.5, y + 0.5);
	find_intersection(&ray, scene);
	if (ray.intersection.distance < MAX_DISTANCE)
		find_shadows(&ray, scene, &reflection_color);
	final->r += ray.intersection.obj_color.r * ray.light_color.r / 255;
	final->b += ray.intersection.obj_color.b * ray.light_color.b / 255;
	final->g += ray.intersection.obj_color.g * ray.light_color.g / 255;
	mix_colors(final, reflection_color);
}

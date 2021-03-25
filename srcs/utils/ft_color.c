/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opposite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:59:20 by gcefalo           #+#    #+#             */
/*   Updated: 2021/02/15 10:32:15 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

t_color	get_trgb(int trgb)
{
	t_color		color;

	color.t = (trgb & (0xFF << 24)) >> 24;
	color.r = (trgb & (0xFF << 16)) >> 16;
	color.g = (trgb & (0xFF << 8)) >> 8;
	color.b = trgb & 0xFF;
	return (color);
}

int		get_light_color(int trgb, double brightness)
{
	t_color	color;

	color = get_trgb(trgb);
	color.r *= brightness;
	color.g *= brightness;
	color.b *= brightness;
	return (create_trgb(0, color.r, color.g, color.b));
}

int		illuminate(t_ray ray)
{
	t_color	final_color;
	t_color	light;
	t_color	object;

	light = get_trgb(ray.light_trgb);
	object = get_trgb(ray.intersection.obj_trgb);
	final_color.r = object.r * light.r / 255;
	final_color.g = object.g * light.g / 255;
	final_color.b = object.b * light.b / 255;
	return (create_trgb(0, final_color.r, final_color.g, final_color.b));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:57:31 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/06 17:04:09 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	positive_atoi(char **line)
{
	int	n;

	n = 0;
	while (**line >= '0' && **line <= '9')
	{
		n *= 10;
		n += **line - '0';
		(*line)++;
	}
	return (n);
}

int	read_int(char **line)
{
	int		n;
	int		minus;

	n = 0;
	minus = 0;
	if (**line == '+')
		(*line)++;
	else if (**line == '-')
	{
		minus = 1;
		(*line)++;
	}
	if (**line >= '0' && **line <= '9')
		n = positive_atoi(line);
	else
	{
		//TODO error: "the element has a wrong format"
	}
	if (minus)
		n *= -1;
	return (n);
}

double	read_double(char **line)
{
	double	i;
	double	d;

	i = 0.;
	d = 0.;
	i = read_int(line);
	if (**line == '.')
	{
		(*line)++;
		if (**line >= '0' && **line <= '9')
		{
			d = positive_atoi(line);
			while ((int)d > 0)
				d /= 10.;
			if (i > 0)
				i += d;
			else
				i -= d;
		}
	}
	return (i);
}

t_color	read_color(char **line)
{
	t_color	color;

	color.t = 0;
	color.r = read_int(line);
	if (!(**line == ',' && *(*line + 1) >= '0' && *(*line + 1) <= '9'))
	{
		//TODO error: "wrong format for color"
	}
	(*line)++;
	color.g = read_int(line);
	if (!(**line == ',' && *(*line + 1) >= '0' && *(*line + 1) <= '9'))
	{
		//TODO error: "wrong format for color"
	}
	(*line)++;
	color.b = read_int(line);
	if (color.r < 0 || color.g < 0 || color.b < 0)
	{
		//TODO error: "color format is incorrect"
	}
	return (color);
}

void	add_element_to_scene(char **line, t_scene *scene)
{
	if (ft_strncmp(*line, "R", 1) == 0)
		create_res(line, scene);
	else if (ft_strncmp(*line, "A", 1) == 0)
		create_amb_l(line, scene);
	else if (ft_strncmp(*line, "pl", 2) == 0)
		create_plane(line, scene);
	else if (ft_strncmp(*line, "sp", 2) == 0)
		create_sph(line, scene);
	else if (ft_strncmp(*line, "sq", 2) == 0)
		create_square(line, scene);
	else if (ft_strncmp(*line, "cy", 2) == 0)
		create_cyl(line, scene);
	else if (ft_strncmp(*line, "tr", 2) == 0)
		create_triangle(line, scene);
	else if (ft_strncmp(*line, "c", 1) == 0)
		create_cam(line, scene);
	else if (ft_strncmp(*line, "l", 1) == 0)
		create_light(line, scene);
	else
	{
		//TODO error: "unrecognized element"
	}
}

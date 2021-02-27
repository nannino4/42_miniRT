/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:57:31 by gcefalo           #+#    #+#             */
/*   Updated: 2021/02/27 17:45:56 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		read_int(char **line)
{
	int		n;

	n = 0;
	while (**line == ' ')
		(*line)++;
	if (**line >= '0' && **line <= '9')
	{
		while (**line >= '0' && **line <= '9')
		{
			n *= 10;
			n += **line - '0';
			(*line)++;
		}
	}
	else
	{
		//TODO error: "the element has a wrong format"
	}
	return (n);
}

double	read_double(char **line)
{
	double	i;
	double	d;

	i = 0.;
	d = 0.;
	i = read_int(line);
	if (**line == '.' && *(*line + 1) != ' ')
	{
		(*line)++;
		d = read_int(line);
		while (d > 0)
			d /= 10.;
		i += d;
	}
		return (i);
}

int		read_color(char **line)
{
	int		r;
	int		g;
	int		b;

	r = read_int(line);
	if (!(**line == ',' && *(*line + 1) >= '0' && *(*line + 1) <= '9'))
		//TODO error: "wrong format for color"
	(*line)++;
	g = read_int(line);
	if (!(**line == ',' && *(*line + 1) >= '0' && *(*line + 1) <= '9'))
		//TODO error: "wrong format for color"
	(*line)++;
	b = read_int(line);
	return (create_trgb(0, r, g, b));
}

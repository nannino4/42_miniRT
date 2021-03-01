/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:57:31 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/01 15:49:00 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	skip_spaces(char **line)
{
	if (**line == ' ')
	{
		while (**line == ' ')
			(*line)++;
	}
	else
	{
		//TODO error: "no space"
	}
}

int		positive_atoi(char **line)
{
	int	n;

	while (**line >= '0' && **line <= '9')
	{
		n *= 10;
		n += **line - '0';
		(*line)++;
	}
	return (n);
}

int		read_int(char **line)
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
			while (d > 0)
				d /= 10.;
			i += d;
		}
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
	if (r < 0 || g < 0 || b < 0)
	{
		//TODO error: "color format is incorrect"
	}
	return (create_trgb(0, r, g, b));
}

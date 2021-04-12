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

int	read_int(char **line, int *minus)
{
	int		n;

	n = 0;
	*minus = 0;
	if (**line == '+')
		(*line)++;
	else if (**line == '-')
	{
		*minus = 1;
		(*line)++;
	}
	if (**line >= '0' && **line <= '9')
		n = positive_atoi(line);
	else
	{
		//TODO error: "the element has a wrong format"
	}
	if (*minus)
		n *= -1;
	return (n);
}

double	read_double(char **line)
{
	double	i;
	double	d;
	int		minus;

	i = 0.;
	d = 0.;
	i = read_int(line, &minus);
	if (**line == '.')
	{
		(*line)++;
		if (**line >= '0' && **line <= '9')
		{
			d = positive_atoi(line);
			while ((int)d > 0)
				d /= 10.;
			if (minus)
				i -= d;
			else
				i += d;
		}
	}
	return (i);
}

t_color	read_color(char **line)
{
	t_color	color;
	int		minus;

	color.t = 0;
	color.r = read_int(line, &minus);
	if (!(**line == ',' && *(*line + 1) >= '0' && *(*line + 1) <= '9'))
	{
		//TODO error: "wrong format for color"
	}
	(*line)++;
	color.g = read_int(line, &minus);
	if (!(**line == ',' && *(*line + 1) >= '0' && *(*line + 1) <= '9'))
	{
		//TODO error: "wrong format for color"
	}
	(*line)++;
	color.b = read_int(line, &minus);
	if (color.r < 0 || color.g < 0 || color.b < 0)
	{
		//TODO error: "color format is incorrect"
	}
	return (color);
}

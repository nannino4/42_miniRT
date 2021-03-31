/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:46:21 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/01 15:48:30 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_p		read_p(char **line)
{
	t_p		p;

	p.x = read_double(line);
	if (**line != ',')
	{
		//TODO error: "invalid point format"
	}
	(*line)++;
	p.y = read_double(line);
	if (**line != ',')
	{
		//TODO error: "invalid point format"
	}
	(*line)++;
	p.z = read_double(line);
	return (p);
}

t_v		read_norm_v(char **line)
{
	t_v		v;

	v.x = read_double(line);
	if (**line != ',')
	{
		//TODO error: "invalid vector format"
	}
	(*line)++;
	v.y = read_double(line);
	if (**line != ',')
	{
		//TODO error: "invalid vector format"
	}
	(*line)++;
	v.z = read_double(line);
	return (v_normalize(v));
}

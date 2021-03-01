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
	p.y = read_double(line);
	p.z = read_double(line);
	return (p);
}

t_v		read_norm_v(char **line)
{
	t_v		v;

	v.x = read_double(line);
	v.y = read_double(line);
	v.z = read_double(line);
	if (v_norm(v) != 1)
	{
		//TODO error: "v is not normalized"
	}
	return (v);
}

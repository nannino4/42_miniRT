/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:26:02 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/06 16:26:48 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_equal(double x, double y)
{
	if (x - y > -1 * EPSILON && x - y < EPSILON)
		return (1);
	else
		return (0);
}

int	is_greater(double x, double y)
{
	if (x - y > EPSILON)
		return (1);
	else
		return (0);
}

t_v	create_v(double x, double y, double z)
{
	t_v		v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_v	v_sum(t_v v1, t_v v2)
{
	t_v		sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

t_v	v_sub(t_v v1, t_v v2)
{
	t_v		sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

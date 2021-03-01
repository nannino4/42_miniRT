/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:26:02 by gcefalo           #+#    #+#             */
/*   Updated: 2021/02/26 15:07:31 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_v		v_sum(t_v v1, t_v v2)
{
	t_v		sum;
	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

t_v		v_sub(t_v v1, t_v v2)
{
	t_v		sub;
	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

t_v		v_scal_mul(t_v v, double a)
{
	v.x *= a;
	v.y *= a;
	v.z *= a;
	return (v);
}

double	v_dot_prod(t_v v1, t_v v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	v_norm(t_v v)
{
	return (sqrt(v_dot_prod(v, v)));
}

t_v		v_normalize(t_v v)
{
	t_v		vec;

	vec.x = v.x / sqrt(v_dot_prod(v, v));
	vec.y = v.y / sqrt(v_dot_prod(v, v));
	vec.z = v.z / sqrt(v_dot_prod(v, v));
	return (vec);
}

t_v		v_cross_prod(t_v v1, t_v v2)
{
	t_v		vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectors_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:24:05 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/06 16:25:35 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	v_norm(t_v v)
{
	return (sqrt(v_dot_prod(v, v)));
}

t_v	v_normalize(t_v v)
{
	t_v		vec;

	vec.x = v.x / sqrt(v_dot_prod(v, v));
	vec.y = v.y / sqrt(v_dot_prod(v, v));
	vec.z = v.z / sqrt(v_dot_prod(v, v));
	return (vec);
}

t_v	v_cross_prod(t_v v1, t_v v2)
{
	t_v		vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

t_p	project_p_to_plane(t_p p, t_p p0, t_v n)
{
	t_v		v;

	v = v_sub(p, p0);
	return (v_sum(p, v_scalar_mul(n, -1 * v_dot_prod(v, n))));
}

t_v	rotate_vector(t_v vector, t_v axis, double a)
{
	double	matrix[3][3];
	t_v		ret;

	matrix[0][0] = axis.x * axis.x + (1 - axis.x * axis.x) * cos(a);
	matrix[0][1] = (1 - cos(a)) * axis.x * axis.y - sin(a) * axis.z;
	matrix[0][2] = (1 - cos(a)) * axis.x * axis.z + sin(a) * axis.y;
	matrix[1][0] = (1 - cos(a)) * axis.x * axis.y + sin(a) * axis.z;
	matrix[1][1] = axis.y * axis.y + (1 - axis.y * axis.y) * cos(a);
	matrix[1][2] = (1 - cos(a)) * axis.y * axis.z - sin(a) * axis.x;
	matrix[2][0] = (1 - cos(a)) * axis.x * axis.z - sin(a) * axis.y;
	matrix[2][1] = (1 - cos(a)) * axis.y * axis.z + sin(a) * axis.x;
	matrix[2][2] = axis.z * axis.z + (1 - axis.z * axis.z) * cos(a);
	ret.x = matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2]
		* vector.z;
	ret.y = matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2]
		* vector.z;
	ret.z = matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2]
		* vector.z;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:21:14 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/06 16:23:21 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	sphere_intercepted(t_ray *ray, double distance, t_sph *sphere)
{
	ray->intersection.distance = distance;
	ray->intersection.hit_point = v_sum(ray->origin,
			v_scalar_mul(ray->direction, distance - EPSILON));
	ray->intersection.obj_color = sphere->color;
	ray->intersection.norm = v_normalize(v_sub(ray->intersection.hit_point,
				sphere->c));
}

int	cylinder_intercepted(t_ray *ray, double t1, t_cyl *cylinder)
{
	double	t;
	t_p		p;
	double	h_test;

	t = t1;
	ray->intersection.hit_point = v_sum(ray->origin,
			v_scalar_mul(ray->direction, t - EPSILON));
	p = project_p_to_plane(ray->intersection.hit_point,
			cylinder->c, cylinder->n);
	h_test = v_norm(v_sub(ray->intersection.hit_point, p));
	if (h_test > cylinder->h || h_test < 0)
		return (0);
	ray->intersection.distance = t;
	ray->intersection.norm = v_normalize(v_sub(p, cylinder->c));
	ray->intersection.obj_color = cylinder->color;
	return (1);
}

t_inters_cy	set_cylinder_variables(t_cyl *cyl, t_ray *ray)
{
	t_inters_cy	cy;

	cy.dir_up = v_dot_prod(ray->direction, cyl->up);
	cy.dir_dx = v_dot_prod(ray->direction, cyl->dx);
	cy.p0_up = v_dot_prod(ray->origin, cyl->up);
	cy.p0_dx = v_dot_prod(ray->origin, cyl->dx);
	return (cy);
}

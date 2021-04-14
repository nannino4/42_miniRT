/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:21:21 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/14 15:46:49 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	intercept_sphere(t_sph *sphere, t_ray *ray)
{
	double		a;
	double		b;
	double		c;

	a = v_dot_prod(ray->direction, ray->direction);
	b = v_dot_prod(v_sub(ray->origin, sphere->c), ray->direction);
	c = v_dot_prod(v_sub(ray->origin, sphere->c), \
			v_sub(ray->origin, sphere->c)) - (sphere->d * sphere->d) / 4;
	if (b * b - a * c < 0)
		return ;
	else if ((-b - sqrt(b * b - a * c)) / a < 0)
	{
		if ((-b + sqrt(b * b - a * c)) / a < 0)
			return ;
		else
			sphere_intercepted(ray, (-b + sqrt(b * b - a * c)) / a, sphere);
	}
	else
		sphere_intercepted(ray, (-b - sqrt(b * b - a * c)) / a, sphere);
}

void	intercept_plane(t_plane *plane, t_ray *ray)
{
	if (is_equal(v_dot_prod(ray->direction, plane->n), 0))
		return ;
	else
	{
		if (v_dot_prod(v_sub(plane->p0, ray->origin), plane->n) \
				 / v_dot_prod(ray->direction, plane->n) < 0)
			return ;
		ray->intersection.distance = v_dot_prod(v_sub(plane->p0, ray->origin), \
				plane->n) / v_dot_prod(ray->direction, plane->n);
		ray->intersection.hit_point = v_sum(ray->origin, \
				v_scalar_mul(ray->direction, \
					ray->intersection.distance - EPSILON));
		ray->intersection.norm = plane->n;
		ray->intersection.obj_color = plane->color;
	}
}

void	intercept_square(t_square *square, t_ray *ray)
{
	t_triangle		triangle_1;
	t_triangle		triangle_2;
	t_triangle		triangle_3;
	t_triangle		triangle_4;
	t_square_points	p;

	p = get_square_points(square);
	triangle_1 = from_sq_to_tr(square->color, p.up_sx, p.up_dx, p.down_sx);
	triangle_2 = from_sq_to_tr(square->color, p.down_dx, p.up_dx, p.down_sx);
	triangle_3 = from_sq_to_tr(square->color, p.up_sx, p.down_dx, p.up_dx);
	triangle_4 = from_sq_to_tr(square->color, p.down_dx, \
			v_scalar_mul(v_sum(p.up_sx, p.up_dx), 0.5), p.down_sx);
	intercept_triangle(&triangle_1, ray);
	intercept_triangle(&triangle_2, ray);
	intercept_triangle(&triangle_3, ray);
	intercept_triangle(&triangle_4, ray);
}

void	intercept_cylinder(t_cyl *cyl, t_ray *ray)
{
	double			a;
	double			b;
	double			c;
	t_inters_cy		cy;

	if (is_equal(v_norm(v_cross_prod(ray->direction, cyl->n)), 0))
		return ;
	cy = set_cylinder_variables(cyl, ray);
	a = cy.dir_up * cy.dir_up + cy.dir_dx * cy.dir_dx;
	b = cy.p0_up * cy.dir_up + cy.p0_dx * cy.dir_dx - cy.dir_up \
		 * cyl->c_up - cy.dir_dx * cyl->c_dx;
	c = cy.p0_up * cy.p0_up + cy.p0_dx * cy.p0_dx - cyl->r * cyl->r
		 + cyl->c_up * cyl->c_up + cyl->c_dx * cyl->c_dx - 2 * (cy.p0_up
			 * cyl->c_up + cy.p0_dx * cyl->c_dx);
	if ((b * b - a * c) < 0)
		return ;
	if ((-b - sqrt(b * b - a * c)) / a < 0)
	{
		if ((-b + sqrt(b * b - a * c)) / a < 0)
			return ;
		cylinder_intercepted(ray, (-b + sqrt(b * b - a * c)) / a, cyl);
		return ;
	}
	if (cylinder_intercepted(ray, (-b - sqrt(b * b - a * c)) / a, cyl))
		return ;
	cylinder_intercepted(ray, (-b + sqrt(b * b - a * c)) / a, cyl);
}

void	intercept_triangle(t_triangle *triangle, t_ray *ray)
{
	t_v				direction;
	double			distance;
	t_inters_tr		tr;

	tr.e1 = v_sub(triangle->p2, triangle->p1);
	tr.e2 = v_sub(triangle->p3, triangle->p1);
	tr.a = v_sub(ray->origin, triangle->p1);
	direction = v_scalar_mul(ray->direction, -1);
	tr.det = v_dot_prod(tr.e1, v_cross_prod(tr.e2, direction));
	distance = v_dot_prod(tr.e1, v_cross_prod(tr.e2, tr.a)) / tr.det;
	tr.u = v_dot_prod(tr.a, v_cross_prod(tr.e2, direction)) / tr.det;
	tr.v = v_dot_prod(tr.e1, v_cross_prod(tr.a, direction)) / tr.det;
	tr.n = v_normalize(v_cross_prod(tr.e1, tr.e2));
	if (!is_equal(v_dot_prod(ray->direction, tr.n), EPSILON) && \
			distance > 0. && tr.u > 0. && tr.v > 0. && (tr.u + tr.v) < 1.)
	{
		ray->intersection.distance = distance;
		ray->intersection.norm = tr.n;
		ray->intersection.hit_point = v_sum(ray->origin, \
				v_scalar_mul(ray->direction, distance - EPSILON));
		ray->intersection.obj_color = triangle->color;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 11:42:39 by gcefalo           #+#    #+#             */
/*   Updated: 2021/02/26 15:08:58 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    sphere_intercepted(t_ray *ray, double distance, t_sph *sphere)
{
    ray->intersection.distance = distance;
    ray->intersection.hit_point = v_sum(ray->origin, v_scalar_mul(ray->direction, distance - EPSILON));
    ray->intersection.obj_color = sphere->color;
    ray->intersection.norm = v_normalize(v_sub(ray->intersection.hit_point, sphere->c));
}

void    intercept_sphere(t_sph *sphere, t_ray *ray)
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

void    intercept_plane(t_plane *plane, t_ray *ray)
{
    if (is_equal(v_dot_prod(ray->direction, plane->n), 0))
        return ;
    else
    {
        if (v_dot_prod(v_sub(plane->p0, ray->origin), plane->n) / v_dot_prod(ray->direction, plane->n) < 0)
            return ;
        ray->intersection.distance = v_dot_prod(v_sub(plane->p0, ray->origin), plane->n) / v_dot_prod(ray->direction, plane->n);
        ray->intersection.hit_point = v_sum(ray->origin, v_scalar_mul(ray->direction, ray->intersection.distance - EPSILON));
        ray->intersection.norm = plane->n;
        ray->intersection.obj_color = plane->color;
    }
}

void    intercept_square(t_square *square, t_ray *ray)
{
    t_triangle  triangle_1;
    t_triangle  triangle_2;
    
    triangle_1.color = square->color;
    triangle_1.n = square->n;
    triangle_1.p1 = v_sum(v_sum(square->c, v_scalar_mul(square->up, square->l / 2.)), v_scalar_mul(square->dx, square->l / -2.));
    triangle_1.p2 = v_sum(v_sum(square->c, v_scalar_mul(square->up, square->l / 2.)), v_scalar_mul(square->dx, square->l / 2.));
    triangle_1.p3 = v_sum(v_sum(square->c, v_scalar_mul(square->up, square->l / -2.)), v_scalar_mul(square->dx, square->l / -2.));
    triangle_2.color = square->color;
    triangle_2.n = square->n;
    triangle_2.p1 = v_sum(v_sum(square->c, v_scalar_mul(square->up, square->l / -2.)), v_scalar_mul(square->dx, square->l / 2.));
    triangle_2.p2 = v_sum(v_sum(square->c, v_scalar_mul(square->up, square->l / 2.)), v_scalar_mul(square->dx, square->l / 2.));
    triangle_2.p3 = v_sum(v_sum(square->c, v_scalar_mul(square->up, square->l / -2.)), v_scalar_mul(square->dx, square->l / -2.));
    intercept_triangle(&triangle_1, ray);
    intercept_triangle(&triangle_2, ray);
}

int     cylinder_intercepted(t_ray *ray, double t1, t_cyl *cylinder)
{
    double  t;
    t_p     p;
    double  h_test;

    t = t1/* / fabs(v_norm(v_cross_prod(ray->direction, cylinder->n)))*/;
    ray->intersection.hit_point = v_sum(ray->origin, v_scalar_mul(ray->direction, t - EPSILON));
    p = project_p_to_plane(ray->intersection.hit_point, cylinder->c, cylinder->n);
    h_test = v_norm(v_sub(ray->intersection.hit_point, p));
    if (h_test > cylinder->h || h_test < 0)
        return (0);
    ray->intersection.distance = t;
    ray->intersection.norm = v_normalize(v_sub(p, cylinder->c));
    ray->intersection.obj_color = cylinder->color;
    return (1);
}

void    set_cylinder_variables(t_cyl *cyl, t_ray *ray)
{
    cyl->dir_up = v_dot_prod(ray->direction, cyl->up);
    cyl->dir_dx = v_dot_prod(ray->direction, cyl->dx);
    cyl->p0_up = v_dot_prod(ray->origin, cyl->up);
    cyl->p0_dx = v_dot_prod(ray->origin, cyl->dx);
}

void    intercept_cylinder(t_cyl *cyl, t_ray *ray)
{
    double  a;
    double  b;
    double  c;

    if (is_equal(v_norm(v_cross_prod(ray->direction, cyl->n)), 0))
        return ;
    set_cylinder_variables(cyl, ray);
    a = cyl->dir_up * cyl->dir_up + cyl->dir_dx * cyl->dir_dx;
    b = cyl->p0_up * cyl->dir_up + cyl->p0_dx * cyl->dir_dx - cyl->dir_up * cyl->c_up - cyl->dir_dx * cyl->c_dx;
    c = cyl->p0_up * cyl->p0_up + cyl->p0_dx * cyl->p0_dx - cyl->r * cyl->r + cyl->c_up * cyl->c_up + cyl->c_dx * cyl->c_dx - 2 * (cyl->p0_up * cyl->c_up + cyl->p0_dx * cyl->c_dx);
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

void    intercept_triangle(t_triangle *triangle, t_ray *ray)
{
    t_v     a;
    t_v     direction;
    double  distance;
    double  tmp;

    triangle->e1 = v_sub(triangle->p2, triangle->p1);
    triangle->e2 = v_sub(triangle->p3, triangle->p1);
    a = v_sub(ray->origin, triangle->p1);
    direction = v_scalar_mul(ray->direction, -1);
    tmp = v_dot_prod(triangle->e1, v_cross_prod(triangle->e2, direction));
    distance = v_dot_prod(triangle->e1, v_cross_prod(triangle->e2, a)) / tmp;
    triangle->u= v_dot_prod(a, v_cross_prod(triangle->e2, direction)) / tmp;
    triangle->v = v_dot_prod(triangle->e1, v_cross_prod(a, direction)) / tmp;
    triangle->n = v_normalize(v_cross_prod(triangle->e1, triangle->e2));
    if (!is_equal(v_dot_prod(ray->direction, triangle->n), EPSILON) && distance > 0. && triangle->u> 0. && triangle->v > 0. && (triangle->u + triangle->v) < 1.)
    {
        ray->intersection.distance = distance;
        ray->intersection.norm = triangle->n;
        ray->intersection.hit_point = v_sum(ray->origin, v_scalar_mul(ray->direction, distance - EPSILON));
        ray->intersection.obj_color = triangle->color;
    }
}

/*
void	intercept_cylinder(t_ray *ray, t_cyl *cy, t_v *n, t_p *p)
{
	t_p         p0;
	t_p         p1;
	t_p         p2;
	t_p         pr;
	t_plane     plb;
	t_plane     plt;
	t_p         s;
	t_p         q;
	t_p         u;
	t_ray		r1;
	t_ray		r2;
	t_sph	    sp;
	t_v         temp;
	double      dist;
	double	    din;
	double	    dout;
	double	    dh;
	double	    dl;
	double	    dq;
	double	    d1;
	double	    d2;
	double	    dt;
	double	    t;

	p1 = v_sum(cy->c, v_scalar_mul(cy->n, cy->h));
	if (is_equal(v_dot_prod(ray->direction, cy->n), 0.))
	{
		plb.p0 = cy->c;
		plb.n = cy->n;
        pr = project_p_to_plane(ray->origin, plb.p0, plb.n);
        d1 = v_norm(v_sub(ray->origin, pr));
		plt.p0 = p1;
		plt.n = cy->n;
		pr = project_p_to_plane(ray->origin, plt.p0, plt.n);
		d2 = v_norm(v_sub(ray->origin, pr));
		if (is_equal(d1 + d2, cy->h))
		{
			p2 = v_sum(plb.p0, v_scalar_mul(plb.n, d1));
			sp.c = p2;
			sp.d = cy->d;
			intercept_sphere(&sp, ray);
            return ;
		}
		else
			return ;
	}
	if (is_greater(0.0, dot_prod(ray->direction, cy->n)))
	{
		p0 = cy->c;
		plb.n = cy->n;
	}
	else
	{
		p0 = p1;
		p1 = cy->c;
		plb.n = v_scalar_mul(cy->n, -1.0);
	}
	plb.p0 = p0;
	pr = project_p_to_plane(ray->origin, plb.p0, plb.n);
	dist = v_norm(v_sub(ray->origin, pr));
	r1.origin = ray->origin;
	r1.direction = ray->direction;
	ray_plane(r1, plb, &temp, &q);
	r2.origin = pr;
	r2.direction = v_normalize(v_sub(q, pr));
	sp.c = p0;
	sp.d = cy->d;
	din = intercept_sphere(r2, sp, &temp, &S);
	if (is_equal(din, DBL_MAX))
		return (DBL_MAX);
	dout = v_norm(v_sub(q, pr));
	dh = dist * (dout - din) / dout;
	if(float_gr(0, dh))
		return (DBL_MAX);
	else if (float_gr(cy->h, dh))
	{
		ray->intersection.hit_point = v_sum(S, v_scalar_mul(plb.n, dh));
		ray->intersection.norm = v_normalize(v_sub(S, p0));
		ray->intersection.distance = sqrt(din * din + (dist - dh) * (dist - dh));
	}
	else
	{
		plt.p0 = p1;
		plt.n = plb.n;
		t = ray_plane(r1, plt, &temp, p);
		dt = v_dist(*p, p1);
		if (float_gr(cy->d / 2.0, dt))
		{
			dl = 2.0 * cy->h - dh;
			dq = dout * dl / dist;
			U = v_sum(pr, v_scalar_mul(r2.direction, dout - dq));
			*p = v_sum(U, v_scalar_mul(plb.n, dl));
			*n = v_norm(v_sub(U, p0);
			return (sqrt((dout - dq) * (dout - dq) + (dist - dl) * (dist - dl)));
		}
		else
			return (DBL_MAX);
	}
}
*/

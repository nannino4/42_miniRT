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
        ray->intersection.distance = MAX_DISTANCE;
	else if ((-b - sqrt(b * b - a * c)) / a < 0 /*EPSILON*/)
    {
        if ((-b + sqrt(b * b - a * c)) / a < 0 /*EPSILON*/)
            ray->intersection.distance = MAX_DISTANCE;
        else
            sphere_intercepted(ray, (-b + sqrt(b * b - a * c)) / a, sphere);
    }
    else
        sphere_intercepted(ray, (-b - sqrt(b * b - a * c)) / a, sphere);
}

void    intercept_plane(t_plane *plane, t_ray *ray)
{
    if (is_equal(v_dot_prod(ray->direction, plane->n), 0))
    {
        ray->intersection.distance = MAX_DISTANCE;
        return ;
    }
    else
    {
        if ((ray->intersection.distance = v_dot_prod(v_sub(plane->p0, ray->origin), plane->n) / v_dot_prod(ray->direction, plane->n)) < EPSILON)
        {
            ray->intersection.distance = MAX_DISTANCE;
            return ;
        }
        ray->intersection.hit_point = v_sum(ray->origin, v_scalar_mul(ray->direction, ray->intersection.distance/* - EPSILON*/));
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

/*
void    intercept_cylinder(t_cyl *cylinder, t_ray *ray)
{

}
*/

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
    if (!is_equal(v_dot_prod(ray->direction, triangle->n), EPSILON) && distance > 0. && triangle->u> 0. && triangle->v > 0. && (triangle->u + triangle->v) < 1.)
    {
        ray->intersection.distance = distance;
        ray->intersection.norm = triangle->n;
        ray->intersection.hit_point = v_sum(ray->origin, v_scalar_mul(ray->direction, distance - EPSILON));
        ray->intersection.obj_color = triangle->color;
    }
}

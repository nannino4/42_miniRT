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
    ray->intersection.obj_trgb = sphere->trgb;
    ray->intersection.norm = v_normalize(v_sub(ray->intersection.hit_point, sphere->c));
}

void    intercept_sphere(t_sph *sphere, t_ray *ray)
{
	double		a;
	double		b;
	double		c;

	a = dot_product(ray->direction, ray->direction);
	b = dot_product(diff(ray->origin, sphere->c), ray->direction);
	c = dot_product(diff(ray->origin, sphere->c), \
            diff(ray->origin, sphere->c)) - (sphere->d * sphere->d) / 4;
	if (b * b - a * c < 0)
        ray->intersection.distance = MAX_DISTANCE + 1;
	else if ((-b - sqrt(b * b - a * c)) / a < EPSILON)
    {
        if ((-b + sqrt(b * b - a * c)) / a < EPSILON)
            ray->intersection.distance = MAX_DISTANCE + 1;
        else
            sphere_intersected(ray, (-b + sqrt(b * b - a * c)) / a, sphere);
    }
    else
        sphere_intercepted(ray, (-b - sqrt(b * b - a * c)) / a, sphere);
}

void    intercept_plane(t_plane *plane, t_ray *ray)
{
    if (is_equal(v_dot_prod(ray->direction, plane->n), 0))
    {
        ray->intersection.distance = MAX_DISTANCE + 1;
        return ;
    }
    else
    {
        if ((ray->intersection.distance = v_dot_prod(v_sub(plane->p0, ray->origin), plane->n) / v_dot_prod(ray->direction, plane->n)) < 0)
        {
            ray->intersection.distance = MAX_DISTANCE + 1;
            return ;
        }
        ray->intersection.hit_point = v_sum(ray->origin, v_scalar_mul(ray->direction, ray->intersection.distance - EPSILON));
        ray->intersection.norm = plane->n;
        ray->intersection.obj_trgb = plane->trgb;
    }
}

void    intercept_square(t_square *square, t_ray *ray)
{

}

void    intercept_cylinder(t_cyl *cylinder, t_ray *ray)
{

}

void    intercept_triangle(t_triangle *triangle, t_ray *ray)
{

}

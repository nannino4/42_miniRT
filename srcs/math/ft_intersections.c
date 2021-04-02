#include "header.h"

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

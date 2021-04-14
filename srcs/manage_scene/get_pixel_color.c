#include "header.h"

void	intersect_obj(t_obj *obj, t_ray *ray)
{
	if (obj->id == SPHERE)
		intercept_sphere((t_sph *)obj->obj, ray);
	if (obj->id == PLANE)
		intercept_plane((t_plane *)obj->obj, ray);
	if (obj->id == SQUARE)
		intercept_square((t_square *)obj->obj, ray);
	if (obj->id == CYLINDER)
		intercept_cylinder((t_cyl *)obj->obj, ray);
	if (obj->id == TRIANGLE)
		intercept_triangle((t_triangle *)obj->obj, ray);
	ray->intersection.intersected_obj = obj;
}

void	find_shadows_2(t_ray *shadow, t_scene *scene, t_light *light_list)
{
	t_obj	*obj_list;

	obj_list = scene->obj;
	while (obj_list)
	{
		intersect_obj(obj_list, shadow);
		if (shadow->intersection.distance
			< v_norm(v_sub(light_list->origin, shadow->origin)))
		{
			shadow->light_color = from_trgb_to_color(0);
			break ;
		}
		obj_list = obj_list->next;
	}	
}

void	find_shadows(t_ray *ray, t_scene *scene, t_color *reflection_color)
{
	t_light		*light_list;
	t_ray		shadow;

	shadow.origin = ray->intersection.hit_point;
	light_list = scene->light;
	while (light_list)
	{
		shadow.direction = v_normalize(v_sub(light_list->origin,
					shadow.origin));
		shadow.light_color = get_light_color(light_list->color,
				light_list->brightness
				* fabs(v_dot_prod(shadow.direction, ray->intersection.norm)));
		shadow.intersection.distance = MAX_DISTANCE;
		find_shadows_2(&shadow, scene, light_list);
		mix_colors(&ray->light_color, shadow.light_color);
		if (shadow.light_color.r || shadow.light_color.g || \
				shadow.light_color.b)
			sum_color(reflection_color, \
					find_reflection(ray, shadow, light_list));
		light_list = light_list->next;
	}
	if (scene->amb_l.brightness > 0)
		mix_colors(&ray->light_color, get_light_color(scene->amb_l.color,
					scene->amb_l.brightness));
}

void	find_intersection(t_ray *ray, t_scene *scene)
{
	double	min_distance;
	t_obj	*obj_list;
	t_obj	*intersected_obj;

	intersected_obj = 0;
	min_distance = MAX_DISTANCE;
	obj_list = scene->obj;
	while (obj_list)
	{
		ray->intersection.distance = MAX_DISTANCE;
		intersect_obj(obj_list, ray);
		if (ray->intersection.distance < min_distance)
		{
			min_distance = ray->intersection.distance;
			intersected_obj = obj_list;
		}
		obj_list = obj_list->next;
	}
	if (intersected_obj)
		intersect_obj(intersected_obj, ray);
}

void	create_ray(t_scene *scene, t_ray *ray, double x, double y)
{
	t_p	p;

	ray->origin = scene->cam->origin;
	p = v_sum(v_sum(scene->screen.p1, v_scalar_mul(scene->cam->dx,
					v_norm(v_sub(scene->screen.p1, scene->screen.p2))
					* x / scene->w)), v_scalar_mul(scene->cam->up,
				-1. * v_norm(v_sub(scene->screen.p1, scene->screen.p4))
				 * y / scene->h));
	ray->direction = v_normalize(v_sub(p, ray->origin));
	ray->light_color = from_trgb_to_color(0);
	ray->intersection.distance = MAX_DISTANCE;
}

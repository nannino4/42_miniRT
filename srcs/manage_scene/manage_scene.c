#include "header.h"

void	create_ray(t_scene *scene, t_ray *ray, double x, double y)
{
	t_v		up;
	t_plane	screen;
	t_p		p1;

	screen.p0 = v_sum(scene->cam->origin, scene->cam->direction);
	screen.n = scene->cam->direction;

	ray->origin = scene->cam->origin;

	if (is_equal(v_dot_prod(scene->cam->direction, create_v(0, 1, 0)), 0))
		up = create_v(0, 1, 0);
	else if(is_equal(v_norm(v_cross_prod(scene->cam->direction, create_v(0, 1, 0))), 0))
		up = create_v(1, 0, 0);
	else
	{
		p1 = project_p_to_plane(create_v(0, 1, 0), screen);
		up = v_normalize(v_sub(p1, screen.p0));
		if(is_greater(0, dot_prod(up, create_v(0, 1, 0))))
			up = v_scalar_mul(up, -1);
	}
}

double	intersect_obj(t_obj *obj, t_ray *ray)
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
}

void	find_intersection(t_ray *ray, t_scene *scene)
{
	double	min_distance;
	t_obj	*list;
	t_obj	*intersected_obj;

	min_distance = MAX_DISTANCE;
	list = scene->obj;
	while (list)
	{
		intersect_obj(list, ray); //fills ray->intersection
		if (ray->intersection.distance < min_distance)
		{
			min_distance = ray->intersection.distance;
			intersected_obj = list;
		}
		list = list->next;
	}
	intersect_obj(intersected_obj, ray);
}

void	find_shadows(t_ray *ray, t_scene *scene)
{
	t_light		*light_list;
	t_obj		*obj_list;
	t_ray		shadow;

	light_list = scene->light;
	shadow.origin = ray->intersection.hit_point;
	shadow.direction = v_sub(light_list->origin, shadow.origin);
	while (light_list)
	{
		obj_list = scene->obj;
		while (obj_list)
		{
			shadow.light.brightness = light_list->brightness;
			intersect_obj(obj_list, &shadow);
			if (shadow.intersection.distance < v_norm(v_sub(light_list->origin, shadow.origin)))
			{
				shadow.light.brightness = 0;
				break ;
			}
			obj_list = obj_list->next;
		}
		shadow.light.brightness *= fabs(v_dot_prod(shadow.direction, ray->intersection.norm));
		//TODO mixcolors(ray);
		light_list = light_list->next;
	}
}

int		get_ray_color(t_ray ray)
{
	//TODO
}

int     get_pixel_color(t_scene *scene, double x, double y)
{
    t_ray	ray;

	create_ray(scene, &ray, x, y);
	find_intersection(&ray, scene);
	find_shadows(&ray, scene);
	return (get_ray_color(ray));
}

void	create_img(t_scene *scene)
{
	double	x;
	double	y;
	t_image	current_img;

	if (scene->img_n == 1)
	{
		current_img = scene->img1;
		scene->img_n = 2;
	}
	else
	{
		current_img = scene->img2;
		scene->img_n = 1;
	}
	current_img.img = mlx_new_image(scene->mlx, scene->w, scene->h);
	current_img.addr = mlx_get_data_addr(current_img.img, current_img.bpp, current_img.line_l, current_img.endian);
	y = 0;
	while (y < scene->h)
	{
		x = 0;
		while (x < scene->w)
			my_mlx_pixel_put(current_img.img, x++, y, get_pixel_color(scene, x, y));
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, current_img.img, 0, 0);
}

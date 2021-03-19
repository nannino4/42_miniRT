#include "header.h"

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
	double	distance;
	t_obj	*list;

	ray->distance = MAX_DISTANCE + 1;
	list = scene->obj;
	while (list)
	{
		distance = intersect_obj(list, ray);
		if (ray->distance > distance)
		{
			ray->distance = distance;
			ray->closest_obj = list;
		}
		list = list->next;
	}
	if (ray->distance >= MAX_DISTANCE)
		ray->closest_obj = 0;
}

int     get_pixel_color(t_scene *scene, double x, double y)
{
    t_ray	ray;

	find_intersection(&ray, scene);
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

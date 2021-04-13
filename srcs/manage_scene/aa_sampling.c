#include "header.h"

void    pixel_with_aa(t_scene *scene, int x, int y, t_color *final)
{
    int     i;
    t_ray	ray;
	double	dltx[4] = {0.2, 0.2, 0.8, 0.8};
	double	dlty[4] = {0.2, 0.8, 0.2, 0.8};
	t_color	reflection_color;

	i = 4;
	reflection_color = from_trgb_to_color(0);
	while (i--)
	{
		create_ray(scene, &ray, x + dltx[i], y + dlty[i]);
		find_intersection(&ray, scene);
		if (ray.intersection.distance < MAX_DISTANCE)
			find_shadows(&ray, scene, &reflection_color);
		final->r += ray.intersection.obj_color.r * ray.light_color.r / 255;
		final->b += ray.intersection.obj_color.b * ray.light_color.b / 255;
		final->g += ray.intersection.obj_color.g * ray.light_color.g / 255;
	}
	*final = divide_color(*final, 4);
	reflection_color = divide_color(reflection_color, 4);
	mix_colors(final, reflection_color);
}

void    pixel_no_aa(t_scene *scene, int x, int y, t_color *final)
{
    t_ray	ray;
	t_color	reflection_color;

	reflection_color = from_trgb_to_color(0);
	create_ray(scene, &ray, x + 0.5, y + 0.5);
	find_intersection(&ray, scene);
	if (ray.intersection.distance < MAX_DISTANCE)
		find_shadows(&ray, scene, &reflection_color);
	final->r += ray.intersection.obj_color.r * ray.light_color.r / 255;
	final->b += ray.intersection.obj_color.b * ray.light_color.b / 255;
	final->g += ray.intersection.obj_color.g * ray.light_color.g / 255;
	mix_colors(final, reflection_color);
}
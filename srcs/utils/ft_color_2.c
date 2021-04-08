#include "header.h"

t_color	find_reflection(t_ray *ray, t_ray shadow, t_light *light_list)
{
	t_color	ret;
	double	ratio;
	t_v		norm;
	t_ray	sp_ray;

	norm = ray->intersection.norm;
	if (v_dot_prod(ray->direction, norm) > 0)
		norm = v_scalar_mul(norm, -1);
	sp_ray.direction = v_sub(ray->direction, v_scalar_mul(norm, 2 * v_dot_prod(ray->direction, norm)));
	ratio = pow(v_dot_prod(shadow.direction, sp_ray.direction), POW_EXP);
	if (ratio < MIN_RATIO || v_dot_prod(shadow.direction, sp_ray.direction) < 0)
		ratio = 0;
	ret.r = get_light_color(light_list->color, light_list->brightness).r * ratio;
	ret.g = get_light_color(light_list->color, light_list->brightness).g * ratio;
	ret.b = get_light_color(light_list->color, light_list->brightness).b * ratio;
	return (ret);
}
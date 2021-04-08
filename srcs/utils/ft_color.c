#include "header.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_color	from_trgb_to_color(int trgb)
{
	t_color		color;

	color.t = (trgb & (0xFF << 24)) >> 24;
	color.r = (trgb & (0xFF << 16)) >> 16;
	color.g = (trgb & (0xFF << 8)) >> 8;
	color.b = trgb & 0xFF;
	return (color);
}

t_color	get_light_color(t_color color, double brightness)
{
	color.r *= brightness;
	color.g *= brightness;
	color.b *= brightness;
	return (color);
}

int	illuminate(t_ray ray)
{
	t_color	final_color;

	final_color.r = ray.intersection.obj_color.r * ray.light_color.r / 255;
	final_color.g = ray.intersection.obj_color.g * ray.light_color.g / 255;
	final_color.b = ray.intersection.obj_color.b * ray.light_color.b / 255;
	return (create_trgb(0, final_color.r, final_color.g, final_color.b));
}

void	mix_colors(t_color *color_1, t_color color_2)
{
	color_1->r = color_1->r + color_2.r;
	color_1->g = color_1->g + color_2.g;
	color_1->b = color_1->b + color_2.b;
	if (color_1->r > 255)
		color_1->r = 255;
	if (color_1->g > 255)
		color_1->g = 255;
	if (color_1->b > 255)
		color_1->b = 255;
}

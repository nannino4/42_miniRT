#include "header.h"

void    create_img(t_scene *scene)
{
	int		x;
	int		y;

	y = 1;
	while (y <= scene->h)
	{
		x = 1;
		while (x <= scene->w)
		{
			my_mlx_pixel_put(scene, x, y, set_pixel(scene, x, y));
			x++;
		}
		y++;
	}
}

int     set_pixel(t_scene *scene, int x, int y)
{
    t_obj       element;
    t_inters    inters_elem;
    t_ray       ray;
    double      d;

    element = scene->obj;
    ray = generate_ray(scene, x, y);
    while (element)
    {
        if ((d = check_intersection(ray, element)) < inters_elem.d)
        {
            inters_elem.obj = element;
        }
        element = element->next;
    }
}

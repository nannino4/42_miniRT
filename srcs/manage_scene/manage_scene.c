#include "header.h"

void	create_screen(t_scene *scene)
{
	scene->screen.plane.p0 = v_sum(scene->cam->origin, scene->cam->direction);
	scene->screen.plane.n = scene->cam->direction;
	if (is_equal(v_dot_prod(scene->cam->direction, create_v(0, 1, 0)), 0))
		scene->screen.up = create_v(0, 1, 0);
	else if(is_equal(v_norm(v_cross_prod(scene->cam->direction, create_v(0, 1, 0))), 0))
		scene->screen.up = create_v(1, 0, 0);
	else
	{
		scene->screen.p1 = project_p_to_plane(v_sum(scene->screen.plane.p0, create_v(0, 1, 0)), scene->screen.plane);
		scene->screen.up = v_normalize(v_sub(scene->screen.p1, scene->screen.plane.p0));
		if(is_greater(0, dot_prod(scene->screen.up, create_v(0, 1, 0))))
			scene->screen.up = v_scalar_mul(scene->screen.up, -1);
	}
	scene->screen.theta = scene->cam->fov * M_PI / 360.;
	scene->screen.dx = v_normalize(v_cross_prod(scene->cam->direction, scene->screen.up));
	scene->screen.p1 = v_sum(v_sum(scene->screen.plane.p0, v_scalar_mul(scene->screen.up, tan(scene->screen.theta) * scene->h / scene->w)), v_scalar_mul(scene->screen.dx, -1. * tan(scene->screen.theta)));
	scene->screen.p2 = v_sum(scene->screen.p1, v_scalar_mul(scene->screen.dx, 2. * tan(scene->screen.theta)));
	scene->screen.p3 = v_sum(scene->screen.p2, v_scalar_mul(scene->screen.up, -2. * tan(scene->screen.theta) * scene->h / scene->w));
	scene->screen.p4 = v_sum(scene->screen.p3, v_scalar_mul(scene->screen.dx, -2. * tan(scene->screen.theta)));
}

int     get_pixel_color(t_scene *scene, double x, double y)
{
    t_ray	ray;

	create_ray(scene, &ray, x, y);
	find_intersection(&ray, scene);
	if (ray.intersection.distance < MAX_DISTANCE)
		find_shadows(&ray, scene);
	return (illuminate(ray));
}

void	create_img(t_scene *scene)
{
	double	x;
	double	y;

	create_screen(scene);
	scene->img_tmp.img = mlx_new_image(scene->mlx, scene->w, scene->h);
	scene->img_tmp.addr = mlx_get_data_addr(scene->img_tmp.img, scene->img_tmp.bpp, scene->img_tmp.line_l, scene->img_tmp.endian);
	y = 0;
	while (y < scene->h)
	{
		x = 0;
		while (x < scene->w)
			my_mlx_pixel_put(scene->img_tmp.img, x++, y, get_pixel_color(scene, x, y));
		y++;
	}
	if (scene->img.img)
		mlx_destroy_image(scene->mlx, scene->img.img);
	scene->img = scene->img_tmp;
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}

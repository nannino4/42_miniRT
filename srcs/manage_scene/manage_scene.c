#include "header.h"

void	create_screen(t_scene *scene)
{
	scene->screen.p0 = v_sum(scene->cam->origin, scene->cam->direction);
	scene->screen.n = scene->cam->direction;
	scene->screen.theta = scene->cam->fov * M_PI / 360.;
	scene->screen.p1 = v_sum(v_sum(scene->screen.p0,
				v_scalar_mul(scene->cam->up, tan(scene->screen.theta)
					* scene->h / scene->w)), v_scalar_mul(scene->cam->dx, -1.
				* tan(scene->screen.theta)));
	scene->screen.p2 = v_sum(scene->screen.p1, v_scalar_mul(scene->cam->dx,
				2. * tan(scene->screen.theta)));
	scene->screen.p3 = v_sum(scene->screen.p2, v_scalar_mul(scene->cam->up,
				-2. * tan(scene->screen.theta) * scene->h / scene->w));
	scene->screen.p4 = v_sum(scene->screen.p3, v_scalar_mul(scene->cam->dx,
				-2. * tan(scene->screen.theta)));
}

int	get_pixel_color(t_scene *scene, double x, double y)
{
    t_ray	ray;
	t_color	final;
	int		i;

	i = AAsamples;
	final.r = 0;
	final.g = 0;
	final.b = 0;
	while(i--)
	{
		create_ray(scene, &ray, x + (float)rand() / (float)RAND_MAX, y + (float)rand() / (float)RAND_MAX);
		find_intersection(&ray, scene);
		if (ray.intersection.distance < MAX_DISTANCE)
			find_shadows(&ray, scene);
		final.r += ray.intersection.obj_color.r * ray.light_color.r / 255;
		final.b += ray.intersection.obj_color.b * ray.light_color.b / 255;
		final.g += ray.intersection.obj_color.g * ray.light_color.g / 255;
	}
	final.r /= AAsamples;
	final.g /= AAsamples;
	final.b /= AAsamples;
	return (create_trgb(0, final.r, final.g, final.b));
}

void	*render_thread(void *arguments)
{
	double		y;
	double		x_temp;
	t_thr_arg	args;

	args = *(t_thr_arg*)arguments;
	x_temp = args.x_start;
	y = 0;
	while (y < args.scene->h)
	{
		args.x_start = x_temp;
		while (args.x_start < args.x_end)
		{
			my_mlx_pixel_put(&args.scene->img, args.x_start, y,
					get_pixel_color(args.scene, args.x_start, y));
			args.x_start++;
		}
		y++;
	}
	return (0);
}

void	create_img(t_scene *scene)
{
	pthread_t	thread_id[thread_count];
	t_thr_arg	args[thread_count];
	int			i;

	create_screen(scene);
	scene->img.img = mlx_new_image(scene->mlx, scene->w, scene->h);
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bpp,
			&scene->img.line_l, &scene->img.endian);
	i = 0;
	while (i < 12)
	{
		args[i].x_start = i * scene->w / 12;
		args[i].x_end = (i + 1) * scene->w / 12;
		args[i].scene = scene;
		pthread_create(&thread_id[i], NULL, render_thread, &args[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread_id[i], NULL);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
	mlx_destroy_image(scene->mlx, scene->img.img);
}

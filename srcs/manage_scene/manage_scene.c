#include "header.h"

void	create_screen(t_scene *scene)
{
	scene->screen.p0 = v_sum(scene->cam->origin, scene->cam->direction);
	scene->screen.n = scene->cam->direction;
	if (is_equal(v_dot_prod(scene->cam->direction, create_v(0, 1, 0)), 0))
		scene->screen.up = create_v(0, 1, 0);
	else if(is_equal(v_norm(v_cross_prod(scene->cam->direction, create_v(0, 1, 0))), 0))
		scene->screen.up = create_v(1, 0, 0);
	else
	{
		scene->screen.p1 = project_p_to_plane(v_sum(scene->screen.p0, create_v(0, 1, 0)), scene->screen.p0, scene->screen.n);
		scene->screen.up = v_normalize(v_sub(scene->screen.p1, scene->screen.p0));
		if(is_greater(0, v_dot_prod(scene->screen.up, create_v(0, 1, 0))))
			scene->screen.up = v_scalar_mul(scene->screen.up, -1);
	}
	scene->screen.theta = scene->cam->fov * M_PI / 360.;
	scene->screen.dx = v_normalize(v_cross_prod(scene->cam->direction, scene->screen.up));
	scene->screen.p1 = v_sum(v_sum(scene->screen.p0, v_scalar_mul(scene->screen.up, tan(scene->screen.theta) * scene->h / scene->w)), v_scalar_mul(scene->screen.dx, -1. * tan(scene->screen.theta)));
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
			my_mlx_pixel_put(&args.scene->img, args.x_start, y, get_pixel_color(args.scene, args.x_start, y));		//create_trgb(0, 255, 0, 0));
			args.x_start++;
		}
		y++;
	}
	return(NULL);
}

void	create_img(t_scene *scene)
{
	pthread_t	thread_id[thread_count];
	t_thr_arg		args[thread_count];
	int			i;

	create_screen(scene);
	scene->img.img = mlx_new_image(scene->mlx, scene->w, scene->h);
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bpp, &scene->img.line_l, &scene->img.endian);
	i = 0;
	while(i < thread_count)
	{
		args[i].x_start = i * scene->w / thread_count;
		args[i].x_end = (i + 1) * scene->w / thread_count;
		//if(i > 1 && args[i].x_start <= args[1 - 1].x_end)
		//	args[i].x_start = args[1 - 1].x_end + 1;
		//if(args[i].x_start > scene->w)
		//	args[i].x_start = scene->w;
		args[i].scene = scene;
		pthread_create(&thread_id[i], NULL, render_thread, &args[i]);
		i++;
	}
	while(i-- > 0)
		pthread_join(thread_id[i], NULL);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
	mlx_destroy_image(scene->mlx, scene->img.img);
	terminal_info();
}

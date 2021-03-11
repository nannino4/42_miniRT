/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:32:12 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/08 18:12:23 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_scene(t_scene *scene)
{
	scene->w = 0;
	scene->h = 0;
	scene->mlx = 0;
	scene->win = 0;
	scene->img = 0;
	scene->addr = 0;
	scene->bpp = 0;
	scene->line_l = 0;
	scene->endian = 0;
	scene->amb_l = 0;
	scene->light = 0;
	scene->cam = 0;
	scene->obj = 0;
}

void	add_element_to_scene(char **line, t_scene *scene)
{
	if (ft_strncmp(*line, "R", 1) == 0)
		create_res(line, scene);
	else if (ft_strncmp(*line, "A", 1) == 0)
		create_amb_l(line, scene);
	else if (ft_strncmp(*line, "c", 1) == 0)
		create_cam(line, scene);
	else if (ft_strncmp(*line, "l", 1) == 0)
		create_light(line, scene);
	else if (ft_strncmp(*line, "pl", 2) == 0)
		create_plane(line, scene);
	else if (ft_strncmp(*line, "sp", 2) == 0)
		create_sph(line, scene);
	else if (ft_strncmp(*line, "sq", 2) == 0)
		create_square(line, scene);
	else if (ft_strncmp(*line, "cy", 2) == 0)
		create_cyl(line, scene);
	else if (ft_strncmp(*line, "tr", 2) == 0)
		create_triangle(line, scene);
	else
	{
		//TODO error: "unrecognized element"
	}
}

void	read_input(t_scene *scene, char *file)
{
	int			fd;
	char		*line;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			add_element_to_scene(&line, scene);
	}
}

/*
void	manage_scene(t_scene scene)
{
	//TODO
}
*/

void	print_status(t_scene scene)
{
	t_light	*l_elem;
	t_cam	*c_elem;
//	t_obj	*o_elem;

	printf("\
w: %d\n\
h: %d\n\
amb_l.t: %lf\n\
amb_l.trgb: %x\n"
, scene.w, scene.h, scene.amb_l->t, scene.amb_l->trgb);
	l_elem = scene.light;
	while (l_elem)
	{
		printf("\
light.t: %lf\n\
light.trgb: %x\n\
light.p.x: %lf\n\
light.p.y: %lf\n\
light.p.z: %lf\n\
light.next: %p\n" \
, l_elem->t, l_elem->trgb, l_elem->p.x, \
				l_elem->p.y, l_elem->p.z, l_elem->next);
		l_elem = l_elem->next;
	}
	c_elem = scene.cam;
	while (c_elem)
	{
		printf("\
cam.p.x: %lf\n\
cam.p.y: %lf\n\
cam.p.z: %lf\n\
cam.v.x: %lf\n\
cam.v.y: %lf\n\
cam.v.z: %lf\n\
cam.fov: %d\n\
cam.next: %p\n" \
, c_elem->p0.x, c_elem->p0.y, c_elem->p0.z, \
				c_elem->v.x, c_elem->v.y, c_elem->v.z, \
				c_elem->fov, c_elem->next);
		c_elem = c_elem->next;
	}
}

int		main(int argc, char **argv)
{
	t_scene		scene;

	init_scene(&scene);
	if (argc == 3 && argv[1] && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		//TODO --save
	}
	else if (argc == 2 && argv[1])
	{
		scene.mlx = mlx_init();
		read_input(&scene, argv[1]);
//		manage_scene(scene);
		print_status(scene);
	}
	else
	{
		//TODO error
	}
	return (0);
}

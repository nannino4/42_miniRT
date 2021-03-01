/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:32:12 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/01 17:28:59 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_data(t_data *data)
{
}

void	add_element_to_scene(char **line, t_scene *scene, t_data *data)
{
	if (ft_strncmp(*line, "R", 1) == 0)
		create_res(line, scene, data);
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
	{
	}
	else
	{
		//TODO error: "unrecognized element"
	}
}

t_scene	read_input(t_data *data, char *file)
{
	t_scene		scene;
	int			fd;
	char		*line;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			add_element_to_scene(&line, &scene, data);
	}
	return (scene);
}

void	manage_scene(t_data data, t_scene scene)
{
	//TODO
}

int		main(int argc, char **argv)
{
	t_data		data;
	t_scene		scene;

	init_data(&data);
	if (argc == 3 && argv[1] && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		//TODO --save
	}
	else if (argc == 2 && argv[1])
	{
		data.mlx = mlx_init();
		scene = read_input(&data, argv[1]);
		manage_scene(data, scene);
	}
	else
	{
		//TODO error
	}
	return (0);
}

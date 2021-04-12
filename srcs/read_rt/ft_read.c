#include "header.h"

int	positive_atoi(char **line)
{
	int	n;

	n = 0;
	while (**line >= '0' && **line <= '9')
	{
		n *= 10;
		n += **line - '0';
		(*line)++;
	}
	return (n);
}

int	read_int(char **line, int *minus, t_scene *scene)
{
	int		n;

	n = 0;
	*minus = 0;
	if (**line == '+')
		(*line)++;
	else if (**line == '-')
	{
		*minus = 1;
		(*line)++;
	}
	if (**line >= '0' && **line <= '9')
		n = positive_atoi(line);
	else
	{
		printf(RED"Error : Invalid number formating\n"RESET);
		exit_func(scene);
	}
	if (*minus)
		n *= -1;
	return (n);
}

double	read_double(char **line, t_scene *scene)
{
	double	i;
	double	d;
	int		minus;

	i = 0.;
	d = 0.;
	i = read_int(line, &minus, scene);
	if (**line == '.')
	{
		(*line)++;
		if (**line >= '0' && **line <= '9')
		{
			d = positive_atoi(line);
			while ((int)d > 0)
				d /= 10.;
			if (minus)
				i -= d;
			else
				i += d;
		}
	}
	return (i);
}

t_color	read_color(char **line, t_scene *scene)
{
	t_color	color;
	int		minus;

	color.t = 0;
	color.r = read_int(line, &minus, scene);
	if (!(**line == ',' && *(*line + 1) >= '0' && *(*line + 1) <= '9'))
	{
		printf(RED"Error : Wrong Color Formatting\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	color.g = read_int(line, &minus, scene);
	if (!(**line == ',' && *(*line + 1) >= '0' && *(*line + 1) <= '9'))
	{
		printf(RED"Error : Wrong Color Formatting\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	color.b = read_int(line, &minus, scene);
	if (color.r < 0 || color.g < 0 || color.b < 0)
	{
		printf(RED"Error : Wrong Color Formatting\n"RESET);
		exit_func(scene);
	}
	return (color);
}

void	add_element_to_scene(char **line, t_scene *scene)
{
	if (ft_strncmp(*line, "R", 1) == 0)
		create_res(line, scene);
	else if (ft_strncmp(*line, "A", 1) == 0)
		create_amb_l(line, scene);
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
	else if (ft_strncmp(*line, "c", 1) == 0)
		create_cam(line, scene);
	else if (ft_strncmp(*line, "l", 1) == 0)
		create_light(line, scene);
	else
	{
		printf(RED"Error : Unrecognized scene element in the .rt file\n"RESET);
		exit_func(scene);
	}
}

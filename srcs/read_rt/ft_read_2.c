#include "header.h"

void	skip_spaces(char **line, t_scene *scene)
{
	if (**line == ' ' || (**line >= 9 && **line <= 13))
	{
		while (**line == ' ' || (**line >= 9 && **line <= 13))
			(*line)++;
	}
	else if (**line)
	{
		printf(RED"Error\nGarbage Text between values\n"RESET);
		exit_func(scene);
	}
}

t_p	read_p(char **line, t_scene *scene)
{
	t_p		p;

	p.x = read_double(line, scene);
	if (**line != ',')
	{
		printf(RED"Error\nInvalid format for point value\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	p.y = read_double(line, scene);
	if (**line != ',')
	{
		printf(RED"Error\nInvalid format for point value\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	p.z = read_double(line, scene);
	return (p);
}

t_v	read_norm_v(char **line, t_scene *scene)
{
	t_v		v;

	v.x = read_double(line, scene);
	if (**line != ',')
	{
		printf(RED"Error\nInvalid format for vector value\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	v.y = read_double(line, scene);
	if (**line != ',')
	{
		printf(RED"Error\nInvalid format for vector value\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	v.z = read_double(line, scene);
	if (is_equal(v.x, 0.) && is_equal(v.y, 0.) && is_equal(v.z, 0.))
	{
		printf(RED"Error\nVersor value cannot be (0, 0, 0)\n"RESET);
		exit_func(scene);
	}
	return (v_normalize(v));
}

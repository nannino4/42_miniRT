#include "header.h"

void	skip_spaces(char **line, t_scene *scene)
{
	if (**line == ' ' || (**line >= 9 && **line <= 13))
	{
		while (**line == ' ' || (**line >= 9 && **line <= 13))
			(*line)++;
	}
	else
	{
		printf(RED"Error : Garbage Text between values\n"RESET);
		exit_func(scene);
	}
}

t_p	read_p(char **line, t_scene *scene)
{
	t_p		p;

	p.x = read_double(line, scene);
	if (**line != ',')
	{
		printf(RED"Error : Invalid format for point value\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	p.y = read_double(line, scene);
	if (**line != ',')
	{
		printf(RED"Error : Invalid format for point value\n"RESET);
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
		printf(RED"Error : Invalid format for vector value\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	v.y = read_double(line, scene);
	if (**line != ',')
	{
		printf(RED"Error : Invalid format for vector value\n"RESET);
		exit_func(scene);
	}
	(*line)++;
	v.z = read_double(line, scene);
	return (v_normalize(v));
}

#include "header.h"

void	create_sph(char **line, t_scene *scene)
{
	t_sph		*sph;

	*line = *line + 2;
	sph = malloc(sizeof(t_sph));
	skip_spaces(line, scene);
	sph->c = read_p(line, scene);
	skip_spaces(line, scene);
	sph->d = read_double(line, scene);
	skip_spaces(line, scene);
	sph->color = read_color(line, scene);
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Sphere values\n"RESET);
		exit_func(scene);
	}
	append_sph(scene, sph);
}

void	create_plane(char **line, t_scene *scene)
{
	t_plane		*plane;

	*line = *line + 2;
	plane = malloc(sizeof(t_plane));
	skip_spaces(line, scene);
	plane->p0 = read_p(line, scene);
	skip_spaces(line, scene);
	plane->n = read_norm_v(line, scene);
	skip_spaces(line, scene);
	plane->color = read_color(line, scene);
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Plane values\n"RESET);
		exit_func(scene);
	}
	append_plane(scene, plane);
}

void	create_square(char **line, t_scene *scene)
{
	t_square		*square;

	*line = *line + 2;
	square = malloc(sizeof(t_square));
	skip_spaces(line, scene);
	square->c = read_p(line, scene);
	skip_spaces(line, scene);
	square->n = read_norm_v(line, scene);
	skip_spaces(line, scene);
	square->l = read_double(line, scene);
	skip_spaces(line, scene);
	square->color = read_color(line, scene);
	set_square_orientation(square);
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Square values\n"RESET);
		exit_func(scene);
	}
	append_square(scene, square);
}

void	create_cyl(char **line, t_scene *scene)
{
	t_cyl		*cyl;

	*line = *line + 2;
	cyl = malloc(sizeof(t_cyl));
	skip_spaces(line, scene);
	cyl->c = read_p(line, scene);
	skip_spaces(line, scene);
	cyl->n = read_norm_v(line, scene);
	skip_spaces(line, scene);
	cyl->r = read_double(line, scene) / 2.;
	skip_spaces(line, scene);
	cyl->h = read_double(line, scene) / 2.;
	skip_spaces(line, scene);
	cyl->color = read_color(line, scene);
	set_cylinder_orientation(cyl);
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Cylinder values\n"RESET);
		exit_func(scene);
	}
	append_cyl(scene, cyl);
}

void	create_triangle(char **line, t_scene *scene)
{
	t_triangle		*triangle;

	*line = *line + 2;
	triangle = malloc(sizeof(t_triangle));
	skip_spaces(line, scene);
	triangle->p1 = read_p(line, scene);
	skip_spaces(line, scene);
	triangle->p2 = read_p(line, scene);
	skip_spaces(line, scene);
	triangle->p3 = read_p(line, scene);
	skip_spaces(line, scene);
	triangle->color = read_color(line, scene);
	skip_spaces(line, scene);
	if (**line)
	{
		printf(RED"Error\nGarbage Text after the Triangle values\n"RESET);
		exit_func(scene);
	}
	append_triangle(scene, triangle);
}

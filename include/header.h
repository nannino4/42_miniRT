/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:33:46 by gcefalo           #+#    #+#             */
/*   Updated: 2021/03/08 17:59:39 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <float.h>

# define BUFFER_SIZE 10
# define MAX_DISTANCE DBL_MAX
# define EPSILON 0.0000000005
# define MAX_W 1920
# define MAX_H 1080

# define SPHERE 0
# define PLANE 1
# define SQUARE 2
# define CYLINDER 3
# define TRIANGLE 4

/*
 * basic structures
 */

typedef struct		s_p
{
	double	x;
	double	y;
	double	z;
}					t_p;

typedef t_p			t_v;

typedef struct		s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}					t_color;

typedef struct		s_inters
{
	double	distance;
	t_color	obj_color;
	t_v		norm;
	t_p		hit_point;
}					t_inters;

typedef struct		s_amb_l
{
	double	brightness;
	t_color	color;
}					t_amb_l;

typedef struct		s_ray
{
	t_p			origin;
	t_v			direction;
	t_inters	intersection;
	t_color		light_color;
}					t_ray;

typedef struct		s_cam
{
	t_p				origin;
	t_v				direction;
	int				fov;
	struct s_cam	*next;
}					t_cam;

typedef struct		s_light
{
	double			brightness;
	t_color			color;
	t_p				origin;
	struct s_light	*next;
}					t_light;

typedef struct		s_obj
{
	int				id;
	void			*obj;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_l;
	int		endian;
}					t_image;

typedef struct		s_screen
{
	t_p		p1;
	t_p		p2;
	t_p		p3;
	t_p		p4;
	t_p		p0;
	t_v		n;
	t_v		up;
	t_v		dx;
	double	theta;
}					t_screen;

typedef struct		s_scene
{
	int			w;
	int			h;
	void		*mlx;
	void		*win;
	t_image		img;
	t_screen	screen;
	t_amb_l		amb_l;
	t_light		*light;
	t_cam		*cam;
	t_obj		*obj;
}					t_scene;

/*
 * geometrical objects
 */

typedef struct		s_sph
{
	t_p			c;
	double		d;
	t_color		color;
}					t_sph;

typedef struct		s_plane
{
	t_p			p0;
	t_v			n;
	t_color		color;
}					t_plane;

typedef struct		s_square
{
	t_p			c;
	t_v			n;
	t_v			up;
	t_v			dx;
	double		l;
	t_color		color;
}					t_square;

typedef struct		s_cyl
{
	t_p			c;
	t_v			n;
	t_v			up;
	t_v			dx;
	double		d;
	double		h;
	t_color		color;
}					t_cyl;

typedef struct		s_triangle
{
	t_p		p1;
	t_p		p2;
	t_p		p3;
	t_v		n;
	t_v		e1;
	t_v		e2;
	double	u;
	double	v;
	t_color	color;
}					t_triangle;

/*
 * math
 */

int		is_equal(double x, double y);
int		is_greater(double x, double y);
t_v		create_v(double x, double y, double z);
t_v		v_sum(t_v v1, t_v v2);
t_v		v_sub(t_v v1, t_v v2);
t_v		v_scalar_mul(t_v v, double a);
double	v_dot_prod(t_v v1, t_v v2);
double	v_norm(t_v v);
t_v		v_normalize(t_v v);
t_v		v_cross_prod(t_v v1, t_v v2);
t_p		project_p_to_plane(t_p p, t_p p0, t_v n);
void    intercept_sphere(t_sph *sphere, t_ray *ray);
void    intercept_plane(t_plane *plane, t_ray *ray);
void    intercept_square(t_square *square, t_ray *ray);
void    intercept_cylinder(t_cyl *cylinder, t_ray *ray);
void    intercept_triangle(t_triangle *triangle, t_ray *ray);

/*
 * utils
 */

int			ft_strncmp(const char *s1, const char *s2, int n);
int			get_next_line(int fd, char **line);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			find_ch(char const *s, char c);
char		*ft_strdup(const char *s1);
void        my_mlx_pixel_put(t_image *img, int x, int y, int trgb);
t_color		get_light_color(t_color color, double brightness);
int			create_trgb(int t, int r, int g, int b);
t_color		from_trgb_to_color(int trgb);
int			illuminate(t_ray ray);
void		mix_colors(t_ray *ray, t_color color);

/*
 * read_input
 */

void	skip_spaces(char **line);
int		read_int(char **line);
double	read_double(char **line);
t_color	read_color(char **line);
t_p		read_p(char **line);
t_v		read_norm_v(char **line);
void	create_res(char **line, t_scene *scene);
void	create_amb_l(char **line, t_scene *scene);
void	create_cam(char **line, t_scene *scene);
void	create_light(char **line, t_scene *scene);
void	create_sph(char **line, t_scene *scene);
void	create_plane(char **line, t_scene *scene);
void	create_square(char **line, t_scene *scene);
void	create_cyl(char **line, t_scene *scene);
void	create_triangle(char **line, t_scene *scene);
void	append_cam(t_scene *scene, t_cam *cam);
void	append_light(t_scene *scene, t_light *light);
void	create_obj(t_scene *scene);
void	append_sph(t_scene *scene, t_sph *sph);
void	append_plane(t_scene *scene, t_plane *plane);
void	append_square(t_scene *scene, t_square *square);
void	append_cyl(t_scene *scene, t_cyl *cyl);
void	append_triangle(t_scene *scene, t_triangle *triangle);
void	set_square_orientation(t_square *square);

/*
 * manage_scene
 */

void	create_img(t_scene *scene);
void	create_ray(t_scene *scene, t_ray *ray, double x, double y);
void	find_intersection(t_ray *ray, t_scene *scene);
void	find_shadows(t_ray *ray, t_scene *scene);

#endif

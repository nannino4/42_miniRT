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

# define BUFFER_SIZE 10
# define MAX_DISTANCE 1000
# define EPSILON 0.05

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
	int		obj_trgb;
	t_v		norm;
	t_p		hit_point;
}					t_inters;

typedef struct		s_amb_l
{
	double	brightness;
	int		trgb;
}					t_amb_l;

typedef struct		s_ray
{
	t_p			origin;
	t_v			direction;
	t_inters	intersection;
	t_amb_l		light;
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
	int				trgb;
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
	t_plane	plane;
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
	int			img_n;
	t_image		img1;
	t_image		img2;
	t_screen	screen;
	t_amb_l		*amb_l;
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
	int			trgb;
}					t_sph;

typedef struct		s_plane
{
	t_p			p0;
	t_v			n;
	int			trgb;
}					t_plane;

typedef struct		s_square
{
	t_p			c;
	t_v			n;
	double		l;
	int			trgb;
}					t_square;

typedef struct		s_cyl
{
	t_p			c;
	t_v			n;
	double		d;
	double		h;
	int			trgb;
}					t_cyl;

typedef struct		s_triangle
{
	t_p		p1;
	t_p		p2;
	t_p		p3;
	int		trgb;
}					t_triangle;

/*
 * ft_math.c
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
t_p		project_p_to_plane(t_p p, t_plane plane);

/*
 * get_trgb.c
 */

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

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
void        my_mlx_pixel_put(t_scene *scene, int x, int y, int trgb);

/*
 * read_input
 */

void	skip_spaces(char **line);
int		read_int(char **line);
double	read_double(char **line);
int		read_color(char **line);
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

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:33:46 by gcefalo           #+#    #+#             */
/*   Updated: 2021/02/27 17:31:07 by gcefalo          ###   ########.fr       */
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

/*
 * essential structures
 */

typedef struct		s_data
{
	int		w;
	int		h;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_l;
	int		endian;
}					t_data;

typedef struct		s_scene
{
	char	*id;
	void	*data;
	void	*next;
}					t_scene;

/*
 * basic structures
 */

typedef struct		s_res
{
	int		x;
	int		y;
}					t_res;

typedef struct		s_p
{
	double	x;
	double	y;
	double	z;
}					t_p;

typedef struct		s_v
{
	double	x;
	double	y;
	double	z;
}					t_v;

typedef struct		s_ray
{
	t_p		p0;
	t_v		v;
}					t_ray;

typedef struct		s_amb_l
{
	double	t;
	int		trgb;
}					t_amb_l;

typedef struct		s_cam
{
	t_p		p0;
	t_v		v;
	int		fov;
}					t_cam;

typedef struct		s_light
{
	double	t;
	int		trgb;
	t_p		p;
}					t_light;

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

t_v		v_sum(t_v v1, t_v v2);
t_v		v_sub(t_v v1, t_v v2);
t_v		v_scal_mul(t_v v, double a);
double	v_dot_prod(t_v v1, t_v v2);
double	v_norm(t_v v);
t_v		v_normalize(t_v v);
t_v		v_cross_prod(t_v v1, t_v v2);

/*
 * get_trgb.c
 */

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

/*
 * libft
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

/*
 * read_input
 */

int		read_int(char **line);
double	read_double(char **line);
int		read_color(char **line);

#endif

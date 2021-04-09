#ifndef HEADER_H
# define HEADER_H

# include "mlx.h"
# include "keycodes.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <float.h>
# include <pthread.h>
# include "ANSI-color-codes.h"

# define BUFFER_SIZE 10
# define MAX_DISTANCE DBL_MAX
# define EPSILON 0.0000000005
# define MOVE_EPSILON 1
# define ROT_EPSILON 0.1
# define BRIGHTNESS_DELTA 0.1
# define DIAMETER_DELTA 1
# define POW_EXP 20
# define MIN_RATIO 0.
# define MAX_W 1920
# define MAX_H 1080
# define AA_SAMPLES 50
# define THREAD_N 12

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

typedef struct		s_obj
{
	int				id;
	void			*obj;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_inters
{
	double	distance;
	t_color	obj_color;
	t_v		norm;
	t_p		hit_point;
	t_obj	*intersected_obj;
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
	t_v				up;
	t_v				dx;
	int				fov;
	struct s_cam	*next;
	struct s_cam	*prev;
}					t_cam;

typedef struct		s_light
{
	double			brightness;
	t_color			color;
	t_p				origin;
	struct s_light	*next;
	struct s_light	*prev;
}					t_light;

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
	t_light		*selected_light;
	t_cam		*cam;
	t_obj		*obj;
	t_obj		*selected_obj;
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

typedef struct		s_inters_cy
{
	double		dir_up;
	double		dir_dx;
	double		p0_up;
	double		p0_dx;
}					t_inters_cy;

typedef struct		s_cyl
{
	t_p			c;
	t_v			n;
	t_v			up;
	t_v			dx;
	double		c_up;
	double		c_dx;
	double		r;
	double		h;
	t_color		color;
}					t_cyl;

typedef struct		s_inters_tr
{
	t_v		a;
	t_v		e1;
	t_v		e2;
	t_v		n;
	double	u;
	double	v;
	double	det;
}					t_inters_tr;

typedef struct		s_triangle
{
	t_p		p1;
	t_p		p2;
	t_p		p3;
	t_color	color;
}					t_triangle;

typedef struct		s_thr_arg
{
	double		x_start;
	double		x_end;
	t_scene		*scene;
}					t_thr_arg;

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
t_v     rotate_vector(t_v vector, t_v axis, double a);
void    intercept_sphere(t_sph *sphere, t_ray *ray);
void    intercept_plane(t_plane *plane, t_ray *ray);
void    intercept_square(t_square *square, t_ray *ray);
void    intercept_cylinder(t_cyl *cylinder, t_ray *ray);
void    intercept_triangle(t_triangle *triangle, t_ray *ray);
void    sphere_intercepted(t_ray *ray, double distance, t_sph *sphere);
int     cylinder_intercepted(t_ray *ray, double t1, t_cyl *cylinder);
t_inters_cy	set_cylinder_variables(t_cyl *cyl, t_ray *ray);

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
void		mix_colors(t_color *color_1, t_color color_2);
t_color	find_reflection(t_ray *ray, t_ray shadow, t_light *light_list);

/*
 * read_rt
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
void	set_cylinder_orientation(t_cyl *cylinder);
void	set_camera_orientation(t_cam *cam);

/*
 * manage_scene
 */

void	create_img(t_scene *scene);
void	create_ray(t_scene *scene, t_ray *ray, double x, double y);
void	find_intersection(t_ray *ray, t_scene *scene);
void	find_shadows(t_ray *ray, t_scene *scene, t_color *reflection_color);

/*
 * input_manager
 */

int 	keyboard_input(int keycode, void *param);
int 	mouse_input(int button, int x, int y, void *param);
void    main_info();

/*
 * input_utils
 */

int     exit_func(void *param);
void	camera_wheel(t_scene *scene);
void	light_wheel(t_scene *scene);
void    transform_camera(t_cam *cam, int key);

/*
 * element_selection
 */

void    select_sphere(t_scene *scene, t_obj *obj);
void    select_light(t_scene *scene);
void    select_triangle(t_scene *scene, t_obj *obj);
void    select_square(t_scene *scene, t_obj *obj);
void    select_cylinder(t_scene *scene, t_obj *obj);
void    select_plane(t_scene *scene, t_obj *obj);

#endif

#include "header.h"

void	move_plane(void *param, t_v axis)
{
	t_plane	*plane;

	plane = (t_plane*)param;
	plane->p0 = v_sum(plane->p0, v_scalar_mul(axis, MOVE_EPSILON));
}

void	rot_plane(void *param, t_v axis)
{
	t_plane	*plane;

	plane = (t_plane *)param;
	plane->n = v_normalize(rotate_vector(plane->n, axis, ROT_EPSILON));
}

void	transform_plane(int key, t_obj *obj, t_cam *cam)
{
	if (key == PG_UP_KEY)
		move_plane(obj->obj, cam->direction);
	else if (key == PG_DOWN_KEY)
		move_plane(obj->obj, v_scalar_mul(cam->direction, -1));
	else if (key == W_KEY)
		move_plane(obj->obj, cam->up);
	else if (key == S_KEY)
		move_plane(obj->obj, v_scalar_mul(cam->up, -1));
	else if (key == D_KEY)
		move_plane(obj->obj, cam->dx);
	else if (key == A_KEY)
		move_plane(obj->obj, v_scalar_mul(cam->dx, -1));
	else if (key == ARROW_UP_KEY)
		rot_plane(obj->obj, cam->dx);
	else if (key == ARROW_DOWN_KEY)
		rot_plane(obj->obj, v_scalar_mul(cam->dx, -1));
	else if (key == ARROW_DX_KEY)
		rot_plane(obj->obj, v_scalar_mul(cam->up, -1));
	else if (key == ARROW_SX_KEY)
		rot_plane(obj->obj, cam->up);
}

int	plane_case_input(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (key == ESC_KEY)
		exit_func(scene);
	else if (key == Q_KEY)
	{
		mlx_key_hook(scene->win, keyboard_input, scene);
		main_info();
	}
	else if (key == PG_UP_KEY || key == PG_DOWN_KEY || key == ARROW_DX_KEY || \
			key == ARROW_DOWN_KEY || key == ARROW_UP_KEY || key == A_KEY || \
			key == S_KEY || key == D_KEY || key == ARROW_SX_KEY || key == W_KEY)
	{
		transform_plane(key, scene->selected_obj, scene->cam);
		create_img(scene);
	}
	else
		printf(YEL "Invalid key pressed...\n"RESET);
	return (1);
}

void	select_plane(t_scene *scene, t_obj *obj)
{
	scene->selected_obj = obj;
	mlx_key_hook(scene->win, plane_case_input, scene);
	system("clear");
	printf(BCYN"PLANE :\n\tW - Move Up\n\t");
	printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
	printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards");
	printf("\n\n\t◀- - Rotate Left\n\t-▶ - Rotate Right");
	printf("\n\t⬇ - Rotate down\n\t⬆ - Rotate Up\n");
	printf(BBLU"\nQ - Exit this mode\n");
	printf("Press ESC or click the close button on the window to exit\n"RESET);
	printf(UGRN"\n----------------------------------------------------------");
	printf("----------------\n\n"RESET);
}

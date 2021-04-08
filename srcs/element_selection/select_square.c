#include "header.h"

void	move_square(void *param, t_v axis)
{
	t_square	*square;

	square = (t_square *)param;
	square->c = v_sum(square->c, v_scalar_mul(axis, MOVE_EPSILON));
}

void	rot_square(void *param, t_v axis)
{
	t_square *square;

	square = (t_square *)param;
	square->n = v_normalize(rotate_vector(square->n, axis, ROT_EPSILON));
	square->up = v_normalize(rotate_vector(square->up, axis, ROT_EPSILON));
	square->dx = v_normalize(rotate_vector(square->dx, axis, ROT_EPSILON));
}

void	square_l_mod(void *param, double delta)
{
	t_square *square;

	square = (t_square *)param;
	square->l += delta;
	if (square->l < 0)
		square->l = 0;
}

void	transform_square(int key, t_obj *obj, t_cam *cam)
{
	if (key == PG_UP_KEY)
		move_square(obj->obj, cam->direction);
	else if (key == PG_DOWN_KEY)
		move_square(obj->obj, v_scalar_mul(cam->direction, -1));
	else if (key == W_KEY)
		move_square(obj->obj, cam->up);
	else if (key == S_KEY)
		move_square(obj->obj, v_scalar_mul(cam->up, -1));
	else if (key == D_KEY)
		move_square(obj->obj, cam->dx);
	else if (key == A_KEY)
		move_square(obj->obj, v_scalar_mul(cam->dx, -1));
	else if (key == ARROW_UP_KEY)
		rot_square(obj->obj, cam->dx);
	else if (key == ARROW_DOWN_KEY)
		rot_square(obj->obj, v_scalar_mul(cam->dx, -1));
	else if (key == ARROW_DX_KEY)
		rot_square(obj->obj, v_scalar_mul(cam->up, -1));
	else if (key == ARROW_SX_KEY)
		rot_square(obj->obj, cam->up);
	else if (key == NUMPAD_PLUS)
		square_l_mod(obj->obj, DIAMETER_DELTA);
	else
		square_l_mod(obj->obj, -DIAMETER_DELTA);
}

int	square_case_input(int key, void *param)
{
	t_scene *scene;

	scene = (t_scene*)param;
	if (key == ESC_KEY)
		exit_func(NULL);
	else if (key == Q_KEY)
	{
		mlx_key_hook(scene->win, keyboard_input, scene);
		main_info();
	}
	else if (key == PG_UP_KEY || key == PG_DOWN_KEY || key == ARROW_DX_KEY || \
			key == ARROW_DOWN_KEY || key == ARROW_UP_KEY || key == A_KEY || \
			key == S_KEY || key == D_KEY || key == ARROW_SX_KEY || key == W_KEY ||
			key == NUMPAD_MINUS || key == NUMPAD_PLUS)
	{
		transform_square(key, scene->selected_obj, scene->cam);
		create_img(scene);
	}
	else
		printf(YEL "Invalid key pressed...\n" reset);
	return (1);
}

void	select_square(t_scene *scene, t_obj *obj)
{
	scene->selected_obj = obj;
	mlx_key_hook(scene->win, square_case_input, scene);
	system("clear");
	printf(BCYN"SQUARE :\n\tW - Move Up\n\t");
	printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
	printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards");
	printf("\n\n\t◀- - Rotate Left\n\t-▶ - Rotate Right");
	printf("\n\t⬇ - Rotate down\n\t⬆ - Rotate Up\n\n");
	printf("\t+ (NumPad) - Increase Lenght\n\t- (NumPad) - Decrease Lenght");
	printf(BBLU"\n\nQ - Exit this mode\n");
	printf("Press ESC or click the close button on the window to exit\n"reset);
	printf(UGRN"\n----------------------------------------------------------");
	printf("----------------\n\n"reset);
}

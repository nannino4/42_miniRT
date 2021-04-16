#include "header.h"

void	rot_square(void *param, t_v axis)
{
	t_square	*square;

	square = (t_square *)param;
	square->n = v_normalize(rotate_vector(square->n, axis, ROT_EPSILON));
	square->up = v_normalize(rotate_vector(square->up, axis, ROT_EPSILON));
	square->dx = v_normalize(rotate_vector(square->dx, axis, ROT_EPSILON));
}

void	square_l_mod(void *param, double delta)
{
	t_square	*square;

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
			key == S_KEY || key == D_KEY || key == ARROW_SX_KEY || \
			key == W_KEY || key == NUMPAD_MINUS || key == NUMPAD_PLUS)
	{
		transform_square(key, scene->selected_obj, scene->cam);
		scene->threading(scene);
	}
	else
		printf(YEL "Invalid key pressed...\n" RESET);
	return (1);
}

void	select_square(t_scene *scene, t_obj *obj)
{
	scene->selected_obj = obj;
	mlx_key_hook(scene->win, square_case_input, scene);
	system("clear");
	printf(\
			BMAG"SQUARE SELECTED :\n\n"\
			BBLU"⇞(Pg Up)"HBLU"\tMove Forwards\n"\
			BBLU"⇟(Pg Down)"HBLU"\tMove Backwards\n\n"\
			BBLU"\tW"HBLU"\tMove Up\n"\
			BBLU"\tS"HBLU"\tMove Down\n"\
			BBLU"\tA"HBLU"\tMove Left\n"\
			BBLU"\tD"HBLU"\tMove Right\n\n"\
			BBLU"\t◀-"HBLU"\tRotate Left\n"\
			BBLU"\t-▶"HBLU"\tRotate Right\n"\
			BBLU"\t⬇"HBLU"\tRotate down\n"\
			BBLU"\t⬆"HBLU"\tRotate Up\n\n"\
			BBLU"+ (NumPad)"HBLU"\tIncrease Lenght\n"\
			BBLU"- (NumPad)"HBLU"\tDecrease Lenght\n\n"\
			BCYN"\tLMB"HCYN"\tLeft Click any object to enter "\
			"it's manipulation mode\n"\
			BCYN"\tRMB"HCYN"\tRight Click in the direction the "\
			"camera should turn\n\n"\
			BHYEL"\tQ"YEL"\tExit this mode\n\n"\
			YEL"Press "BHYEL"ESC"YEL" or click the close button on "\
			"the view window to exit\n"\
			UGRN"\n----------------------------------------------------------"\
			"----------------\n\n"RESET);
}

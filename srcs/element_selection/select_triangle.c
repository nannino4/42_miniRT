#include "header.h"

void	move_triangle(void *param, t_v direction)
{
	t_triangle	*triangle;

	triangle = (t_triangle*)param;
	triangle->p1 = v_sum(triangle->p1, v_scalar_mul(direction, MOVE_EPSILON));
	triangle->p2 = v_sum(triangle->p2, v_scalar_mul(direction, MOVE_EPSILON));
	triangle->p3 = v_sum(triangle->p3, v_scalar_mul(direction, MOVE_EPSILON));
}

void	transform_triangle(int key, t_obj *obj, t_scene *scene)
{
	if (key == PG_UP_KEY)
		move_triangle(obj->obj, scene->cam->direction);
	else if (key == PG_DOWN_KEY)
		move_triangle(obj->obj, v_scalar_mul(scene->cam->direction, -1));
	else if (key == W_KEY)
		move_triangle(obj->obj, scene->cam->up);
	else if (key == S_KEY)
		move_triangle(obj->obj, v_scalar_mul(scene->cam->up, -1));
	else if (key == D_KEY)
		move_triangle(obj->obj, scene->cam->dx);
	else if (key == A_KEY)
		move_triangle(obj->obj, v_scalar_mul(scene->cam->dx, -1));
}

int	triangle_case_input(int key, void *param)
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
	else if (key == PG_UP_KEY || key == PG_DOWN_KEY || key == W_KEY || \
			key == S_KEY || key == D_KEY || key == A_KEY)
	{
		transform_triangle(key, scene->selected_obj, scene);
		scene->threading(scene);
	}
	else
		printf(YEL "Invalid key pressed...\n" RESET);
	return (1);
}

void	select_triangle(t_scene *scene, t_obj *obj)
{
	scene->selected_obj = obj;
	mlx_key_hook(scene->win, triangle_case_input, scene);
	system("clear");
	printf(\
			BMAG"TRIANGLE SELECTED :\n\n"\
			BBLU"⇞(Pg Up)"HBLU"\tMove Forwards\n"\
			BBLU"⇟(Pg Down)"HBLU"\tMove Backwards\n\n"\
			BBLU"\tW"HBLU"\tMove Up\n"\
			BBLU"\tS"HBLU"\tMove Down\n"\
			BBLU"\tA"HBLU"\tMove Left\n"\
			BBLU"\tD"HBLU"\tMove Right\n\n"\
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

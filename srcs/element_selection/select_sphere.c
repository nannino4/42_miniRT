#include "header.h"

void	sphere_translation(void *param, t_v direction)
{
	t_sph	*sphere;

	sphere = (t_sph*)param;
	sphere->c = v_sum(sphere->c, v_scalar_mul(direction, MOVE_EPSILON));
}

void	sphere_diameter_mod(void *param, double delta)
{
	t_sph	*sphere;

	sphere = (t_sph*)param;
	sphere->d += delta;
	if (sphere->d < 0)
		sphere->d = 0;
}

void	sphere_mod_key(int key, t_obj *obj, t_scene *scene)
{
	if (key == PG_UP_KEY)
		sphere_translation(obj->obj, scene->cam->direction);
	else if (key == PG_DOWN_KEY)
		sphere_translation(obj->obj, v_scalar_mul(scene->cam->direction, -1));
	else if (key == W_KEY)
		sphere_translation(obj->obj, scene->cam->up);
	else if (key == S_KEY)
		sphere_translation(obj->obj, v_scalar_mul(scene->cam->up, -1));
	else if (key == D_KEY)
		sphere_translation(obj->obj, scene->cam->dx);
	else if (key == A_KEY)
		sphere_translation(obj->obj, v_scalar_mul(scene->cam->dx, -1));
	else if (key == NUMPAD_PLUS)
		sphere_diameter_mod(obj->obj, DIAMETER_DELTA);
	else
		sphere_diameter_mod(obj->obj, -DIAMETER_DELTA);
}

int	sphere_case_input(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (key == 53)
		exit_func(scene);
	else if (key == 12)
	{
		mlx_key_hook(scene->win, keyboard_input, scene);
		main_info();
	}
	else if (key == PG_UP_KEY || key == PG_DOWN_KEY || key == W_KEY || \
			key == S_KEY || key == D_KEY || key == A_KEY || \
			key == NUMPAD_MINUS || key == NUMPAD_PLUS)
	{
		sphere_mod_key(key, scene->selected_obj, scene);
		scene->threading(scene);
	}
	else
		printf(YEL "Invalid key pressed...\n" RESET);
	return (1);
}

void	select_sphere(t_scene *scene, t_obj *obj)
{
	scene->selected_obj = obj;
	mlx_key_hook(scene->win, sphere_case_input, scene);
	system("clear");
	printf(\
			BMAG"SPHERE SELECTED :\n\n"\
			BBLU"⇞(Pg Up)"HBLU"\tMove Forwards\n"\
			BBLU"⇟(Pg Down)"HBLU"\tMove Backwards\n\n"\
			BBLU"\tW"HBLU"\tMove Up\n"\
			BBLU"\tS"HBLU"\tMove Down\n"\
			BBLU"\tA"HBLU"\tMove Left\n"\
			BBLU"\tD"HBLU"\tMove Right\n\n"\
			BBLU"+ (NumPad)"HBLU"\tIncrease Diameter\n"\
			BBLU"- (NumPad)"HBLU"\tDecrease Diameter\n\n"\
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

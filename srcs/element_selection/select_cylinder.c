#include "header.h"

void	cylinder_axis_mod(void *param, t_v axis, int key)
{
	t_cyl	*cyl;

	cyl = (t_cyl *)param;
	if (key == S_KEY || key == PG_DOWN_KEY || key == A_KEY || \
			key == PG_UP_KEY || key == D_KEY || key == W_KEY)
		cyl->c = v_sum(cyl->c, v_scalar_mul(axis, MOVE_EPSILON));
	else if (key == ARROW_DX_KEY || key == ARROW_DOWN_KEY || \
			key == ARROW_UP_KEY || key == ARROW_SX_KEY)
	{
		cyl->n = v_normalize(rotate_vector(cyl->n, axis, ROT_EPSILON));
		cyl->up = v_normalize(rotate_vector(cyl->up, axis, ROT_EPSILON));
		cyl->dx = v_normalize(rotate_vector(cyl->dx, axis, ROT_EPSILON));
	}
	set_cylinder_orientation(cyl);
}

void	cylinder_metrics_mod(void *param, double delta, int key)
{
	t_cyl	*cylinder;

	cylinder = (t_cyl *)param;
	if (key == NUMPAD_PLUS)
		cylinder->h += delta / 2;
	else if (key == NUMPAD_MINUS)
		cylinder->h -= delta / 2;
	else if (key == Z_KEY)
		cylinder->r -= delta / 2;
	else if (key == X_KEY)
		cylinder->r += delta / 2;
	if (cylinder->h < 0)
		cylinder->h = 0;
	if (cylinder->r < 0)
		cylinder->r = 0;
}

void	transform_cylinder(int key, t_obj *obj, t_cam *cam)
{
	if (key == PG_UP_KEY)
		cylinder_axis_mod(obj->obj, cam->direction, key);
	else if (key == PG_DOWN_KEY)
		cylinder_axis_mod(obj->obj, v_scalar_mul(cam->direction, -1), key);
	else if (key == W_KEY)
		cylinder_axis_mod(obj->obj, cam->up, key);
	else if (key == S_KEY)
		cylinder_axis_mod(obj->obj, v_scalar_mul(cam->up, -1), key);
	else if (key == D_KEY)
		cylinder_axis_mod(obj->obj, cam->dx, key);
	else if (key == A_KEY)
		cylinder_axis_mod(obj->obj, v_scalar_mul(cam->dx, -1), key);
	else if (key == ARROW_UP_KEY)
		cylinder_axis_mod(obj->obj, cam->dx, key);
	else if (key == ARROW_DOWN_KEY)
		cylinder_axis_mod(obj->obj, v_scalar_mul(cam->dx, -1), key);
	else if (key == ARROW_DX_KEY)
		cylinder_axis_mod(obj->obj, v_scalar_mul(cam->up, -1), key);
	else if (key == ARROW_SX_KEY)
		cylinder_axis_mod(obj->obj, cam->up, key);
	else if (key == NUMPAD_PLUS || key == X_KEY || key == Z_KEY \
			 || key == NUMPAD_MINUS)
		cylinder_metrics_mod(obj->obj, DIAMETER_DELTA, key);
}

int	cylinder_case_input(int key, void *param)
{
	t_scene	*scene;

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
			key == S_KEY || key == D_KEY || key == ARROW_SX_KEY || \
			key == W_KEY || key == NUMPAD_MINUS || key == NUMPAD_PLUS || \
			key == X_KEY || key == Z_KEY)
	{
		transform_cylinder(key, scene->selected_obj, scene->cam);
		create_img(scene);
	}
	else
		printf(YEL "Invalid key pressed...\n" reset);
	return (1);
}

void	select_cylinder(t_scene *scene, t_obj *obj)
{
	scene->selected_obj = obj;
	mlx_key_hook(scene->win, cylinder_case_input, scene);
	system("clear");
	printf(BCYN"CYLINDER :\n\tW - Move Up\n\t");
	printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
	printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards");
	printf("\n\n\t◀- - Rotate Left\n\t-▶ - Rotate Right");
	printf("\n\t⬇ - Rotate down\n\t⬆ - Rotate Up\n\n");
	printf("\t+ (NumPad) - Increase Height\n\t- (NumPad) - Decrease Height");
	printf("\n\tX - Increase Diameter\n\tZ - Decrease Diameter");
	printf(BBLU"\n\nQ - Exit this mode\n");
	printf("Press ESC or click the close button on the window to exit\n"reset);
	printf(UGRN"\n----------------------------------------------------------");
	printf("----------------\n\n"reset);
}

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
	printf("key pressed : %d\n", key);
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
		create_img(scene);
	}
	else
		printf(YEL "Invalid key pressed...\n" reset);
	return (1);
}

void	select_sphere(t_scene *scene, t_obj *obj)
{
	scene->selected_obj = obj;
	mlx_key_hook(scene->win, sphere_case_input, scene);
	system("clear");
	printf(BCYN"SPHERE :\n\tW - Move Up\n\t");
	printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
	printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards\n\n\t");
	printf("+ (NumPad) - Increase Diameter\n\t- (NumPad) - Decrease Diameter");
	printf(BBLU"\n\nQ - Exit this mode\n");
	printf("Press ESC or click the close button on the window to exit\n"reset);
	printf(UGRN"\n----------------------------------------------------------");
	printf("----------------\n\n"reset);
}

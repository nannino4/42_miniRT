#include "header.h"

void	move_light(t_light *light, t_v axis)
{
	light->origin = v_sum(light->origin, v_scalar_mul(axis, MOVE_EPSILON));
}

void	transform_light(t_scene *scene, t_light *light, int key)
{
	if (key == PG_UP_KEY)
		move_light(light, scene->cam->direction);
	else if (key == PG_DOWN_KEY)
		move_light(light, v_scalar_mul(scene->cam->direction, -1));
	else if (key == W_KEY)
		move_light(light, scene->cam->up);
	else if (key == S_KEY)
		move_light(light, v_scalar_mul(scene->cam->up, -1));
	else if (key == D_KEY)
		move_light(light, scene->cam->dx);
	else if (key == A_KEY)
		move_light(light, v_scalar_mul(scene->cam->dx, -1));
	else if (key == NUMPAD_PLUS)
	{
		light->brightness += BRIGHTNESS_DELTA;
		if (light->brightness > 1)
			light->brightness = 1;
	}
	else
	{
		light->brightness -= BRIGHTNESS_DELTA;
		if (light->brightness < 0)
			light->brightness = 0;
	}
}

int	light_case_input(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	printf("key pressed : %d\n", key);
	if (key == 53)
		exit_func(NULL, scene);
	else if (key == 12)
	{
		mlx_key_hook(scene->win, keyboard_input, scene);
		main_info();
	}
	else if (key == L_KEY)
		light_wheel(scene);
	else if (key == PG_UP_KEY || key == PG_DOWN_KEY || key == W_KEY || \
			key == S_KEY || key == D_KEY || key == A_KEY || key == NUMPAD_PLUS \
			 || key == NUMPAD_MINUS)
	{
		transform_light(scene, scene->selected_light, key);
		create_img(scene);
	}
	else
		printf(YEL "Invalid key pressed...\n" reset);
	return (1);
}

void	select_light(t_scene *scene)
{
	scene->selected_light = scene->light;
	mlx_key_hook(scene->win, light_case_input, scene);
	system("clear");
	printf(BCYN"LIGHT :\n\tW - Move Up\n\t");
	printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
	printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards\n\n\t");
	printf("+(NumPad) - Increase Brightness\n\t-(NumPad) - Decrease Brightness");
	printf("\n\n\tL - Select next light"BBLU"\n\nQ - Exit selection");
	printf("\nPress ESC or click the close button on the window to exit\n"reset);
	printf(UGRN"\n----------------------------------------------------------");
	printf("----------------\n\n"reset);
}

#include "header.h"
#include "ANSI-color-codes.h"

void    sphere_translation(void *param, t_v direction)
{
    t_sph   *sphere;

    sphere = (t_sph*)param;
    sphere->c = v_sum(sphere->c, v_scalar_mul(direction, MOVE_EPSILON));
}

void    sphere_move_key(int key, t_obj *obj, t_scene *scene)
{
    if (key == MOVE_FORWARD)
		sphere_translation(obj->obj, scene->cam->direction);
	else if (key == MOVE_BACK)
		sphere_translation(obj->obj, v_scalar_mul(scene->cam->direction, -1));
	else if (key == MOVE_UP)
		sphere_translation(obj->obj, scene->cam->up);
	else if (key == MOVE_DOWN)
		sphere_translation(obj->obj, v_scalar_mul(scene->cam->up, -1));
	else if (key == MOVE_DX)
		sphere_translation(obj->obj, scene->cam->dx);
	else if (key == MOVE_SX)
		sphere_translation(obj->obj, v_scalar_mul(scene->cam->dx, -1));
	//else if (key == NUMPAD_PLUS)
	//	rot_camera(cam, cam->dx);
	//else if (key == NUMPAD_MINUS)
	//	rot_camera(cam, v_scalar_mul(cam->dx, -1));
    else
        printf("Work_IN_Progress\n");
}

int    sphere_case_input(int key, void   *param)
{
	t_manip_data	*data;

	data = (t_manip_data*)param;
	printf("key pressed : %d\n", key);
	if (key == 53)
		exit_func(NULL);
    else if (key == 12)
    {
        mlx_key_hook(data->scene->win, keyboard_input, data->scene);
        main_info();
    }
    else if (key == MOVE_FORWARD || key == MOVE_BACK || key == MOVE_UP || \
			key == MOVE_DOWN || key == MOVE_DX || key == MOVE_SX)
        {
            sphere_move_key(key, data->obj, data->scene);
            create_img(data->scene);
        }
    else
        printf(YEL "Invalid key pressed...\n" reset);
    return 1;
}
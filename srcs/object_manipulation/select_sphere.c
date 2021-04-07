#include "header.h"

void    move_sphere(void *param, t_v direction)
{
    t_sph   *sphere;

    sphere = (t_sph*)param;
    sphere->c = v_sum(sphere->c, v_scalar_mul(direction, MOVE_EPSILON));
}

void    transform_sphere(int key, t_obj *obj, t_scene *scene)
{
    if (key == MOVE_FORWARD)
		move_sphere(obj->obj, scene->cam->direction);
	else if (key == MOVE_BACK)
		move_sphere(obj->obj, v_scalar_mul(scene->cam->direction, -1));
	else if (key == MOVE_UP)
		move_sphere(obj->obj, scene->cam->up);
	else if (key == MOVE_DOWN)
		move_sphere(obj->obj, v_scalar_mul(scene->cam->up, -1));
	else if (key == MOVE_DX)
		move_sphere(obj->obj, scene->cam->dx);
	else if (key == MOVE_SX)
		move_sphere(obj->obj, v_scalar_mul(scene->cam->dx, -1));
	else if (key == NUMPAD_PLUS)
        ((t_sph *)obj->obj)->d += DIAMETER_DELTA;
	else
    {
        ((t_sph *)obj->obj)->d -= DIAMETER_DELTA;
        if (((t_sph *)obj->obj)->d < 0)
            ((t_sph *)obj->obj)->d = 0;
    }
}

int    sphere_case_input(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	printf("key pressed : %d\n", key);
	if (key == 53)
		exit_func(NULL);
    else if (key == 12)
    {
        mlx_key_hook(scene->win, keyboard_input, scene);
        main_info();
    }
    else if (key == MOVE_FORWARD || key == MOVE_BACK || key == MOVE_UP || \
			key == MOVE_DOWN || key == MOVE_DX || key == MOVE_SX)
        {
            transform_sphere(key, scene->selected_obj, scene);
            create_img(scene);
        }
    else
        printf(YEL "Invalid key pressed...\n" reset);
    return 1;
}

void    select_sphere(t_scene *scene, t_obj *obj)
{
    scene->selected_obj = obj;
    mlx_key_hook(scene->win, sphere_case_input, scene);
    system("clear");
    printf(BCYN"SPHERE :\n\tW - Move Up\n\t");
    printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
    printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards\n\n\t");
    printf("+ (NumPad) - Increase Diameter\n\t- (NumPad) - Decrease Diameter");
    printf("\nQ - Exit selection");
    printf(BBLU"\nPress ESC or click the close button on the window to exit\n"reset);
}

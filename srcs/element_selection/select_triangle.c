#include "header.h"

void    move_triangle(void *param, t_v direction)
{
    t_triangle *triangle;

    triangle = (t_triangle*)param;
    triangle->p1 = v_sum(triangle->p1, v_scalar_mul(direction, MOVE_EPSILON));
    triangle->p2 = v_sum(triangle->p2, v_scalar_mul(direction, MOVE_EPSILON));
    triangle->p3 = v_sum(triangle->p3, v_scalar_mul(direction, MOVE_EPSILON));
}

void    transform_triangle(int key, t_obj *obj, t_scene *scene)
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

int     triangle_case_input(int key, void *param)
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
    else if (key == PG_UP_KEY || key == PG_DOWN_KEY || key == W_KEY || \
			key == S_KEY || key == D_KEY || key == A_KEY)
        {
            transform_triangle(key, scene->selected_obj, scene);
            create_img(scene);
        }
    else
        printf(YEL "Invalid key pressed...\n" reset);
    return 1;
}

void    select_triangle(t_scene *scene, t_obj *obj)
{
    scene->selected_obj = obj;
    mlx_key_hook(scene->win, triangle_case_input, scene);
    system("clear");
    printf(BCYN"TRIANGLE :\n\tW - Move Up\n\t");
    printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
    printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards\n");
    printf(BBLU"\nQ - Exit this mode\n");
    printf("Press ESC or click the close button on the window to exit\n"reset);
    printf(UGRN"\n----------------------------------------------------------");
    printf("----------------\n\n"reset);
}
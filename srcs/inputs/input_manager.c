#include "header.h"

int keyboard_input(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	printf("key pressed : %d\n", key);
	if (key == ESC_KEY)
		exit_func(NULL);
	else if (key == C_KEY)
		camera_wheel(scene);
	else if (key == PG_UP_KEY || key == PG_DOWN_KEY || key == ARROW_DX_KEY || \
			key == ARROW_DOWN_KEY || key == ARROW_UP_KEY || key == A_KEY || \
			key == S_KEY || key == D_KEY || key == ARROW_SX_KEY || key == W_KEY)
	{
		transform_camera(scene->cam, key);
		create_img(scene);
	}
    else if (key == L_KEY)
        select_light(scene);
	return (key);
}

int	mouse_input(int button, int x, int y, void *param)
{
    t_scene *scene;
    t_ray   ray;

    scene = (t_scene *)param;
    //printf("pressed mouse button : %d at %d,%d\n", button, x, y);
    if(button == 1)
    {
        create_ray(scene, &ray, (double)x + 0.5, (double)y + 0.5);
        find_intersection(&ray, scene);
        if(ray.intersection.distance < MAX_DISTANCE)
        {
            if(ray.intersection.intersected_obj->id == SPHERE)
                select_sphere(scene, ray.intersection.intersected_obj);
            else if(ray.intersection.intersected_obj->id == PLANE)
                select_plane(scene, ray.intersection.intersected_obj);
            else if(ray.intersection.intersected_obj->id == CYLINDER)
                select_cylinder(scene, ray.intersection.intersected_obj);
            else if(ray.intersection.intersected_obj->id == TRIANGLE)
                select_triangle(scene, ray.intersection.intersected_obj);
            else if(ray.intersection.intersected_obj->id == SQUARE)
                select_square(scene, ray.intersection.intersected_obj);
        }
        else
            printf(YEL"No object where clicked\n"reset);
    }

    // printi info su oggetto selezionato e istruzioni per interagirci
    return 1;
}

void	main_info(void)
{
    system("clear");
    printf(BCYN"CAMERA :\n\tW - Move Up\n\t");
    printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
    printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards\n");
    printf("\n\t◀- - Rotate Left\n\t");
    printf("-▶ - Rotate Right\n\t⬇ - Rotate down\n\t");
    printf("⬆ - Rotate Up\n\n\tC - Cycle cameras\n\tL - Cycle Lights\n\n");
    printf(BBLU"Press ESC or click the close button on the view window to exit\n"reset);
    printf(UGRN"\n----------------------------------------------------------");
    printf("----------------\n\n"reset);
}

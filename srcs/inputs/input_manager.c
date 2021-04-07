#include "header.h"
#include "ANSI-color-codes.h"

int	keyboard_input(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	printf("key pressed : %d\n", key);
	if (key == 53)
		exit_func(NULL);
	else if (key == 8)
		camera_wheel(scene);
	else if (key == MOVE_FORWARD || key == MOVE_BACK || key == MOVE_UP || \
			key == MOVE_DOWN || key == MOVE_DX || key == MOVE_SX || \
			key == ROT_UP || key == ROT_DOWN || key == ROT_DX || key == ROT_SX)
	{
		transform_camera(scene->cam, key);
		create_img(scene);
	}
	return (key);
}

int	mouse_input(int button, int x, int y, void *param)
{
    t_scene *scene;
    t_ray   ray;

    scene = (t_scene*)param;
    //printf("pressed mouse button : %d at %d,%d\n", button, x, y);
    if(button == 1)
    {
        create_ray(scene, &ray, (double)x + 0.5, (double)y + 0.5);
        find_intersection(&ray, scene);
        if(ray.intersection.distance < MAX_DISTANCE)
        {
            if(ray.intersection.intersected_obj->id == SPHERE)
                sphere_manip(scene, ray.intersection.intersected_obj);
            //else if(ray.intersection.intersected_obj->id == PLANE)
            //    plane_manip();
            //else if(ray.intersection.intersected_obj->id == CYLINDER)
            //    cylinder_manip();
            //else if(ray.intersection.intersected_obj->id == TRIANGLE)
            //    triangle_manip();
            //else if(ray.intersection.intersected_obj->id == SQUARE)
            //    square_manip();
        }
        else
            printf("No object where clicked\n");
    }

    // printi info su oggetto selezionato e istruzioni per interagirci
    return 1;
}
int     terminal_input(void *param)
{
    t_scene *scene;
    char    *temp="A.";
    char    *line;

    scene = (t_scene*)param;
    usleep(100000);
    if(get_next_line(0, &line) == 1)
    {
        //printf("%s", line);
        write(1, temp, 2);
	    mlx_loop_hook(scene->mlx, NULL, scene);
    }
    // controllo oggetto selezionato
    // gnl legge input da terminale e lo usa in base all'oggetto selezionato
    return 1;
}

void	main_info(void)
{
    system("clear");
    printf(BCYN"CAMERA MOVEMENT :\n\tW - Move Up\n\t");
    printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
    printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards\n");
    printf("CAMERA ROTATION\n\t◀- - Rotate Left\n\t");
    printf("-▶ - Rotate Right\n\t⬇ - Rotate down\n\t");
    printf("⬆ - Rotate Up\n\n\tC - Cycle cameras\n\n");
    printf(BBLU"Press ESC or click the close button on the window to exit\n"reset);
    printf("Enter any commands through the terminal ...\n");
}

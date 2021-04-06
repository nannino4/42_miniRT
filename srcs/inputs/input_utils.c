#include "header.h"
#include "ANSI-color-codes.h"

int	exit_func(void *param)
{
	if (param == NULL)
		printf("EXITING\n");
	exit(0);
	return (0);
}

void	camera_wheel(t_scene *scene)
{
    if(scene->cam->next !=NULL || scene->cam->prev != NULL)
    {
        if(scene->cam->next != NULL)
        {
            printf("Switching Camera\n");
            scene->cam = scene->cam->next;
        }
        else
        {
            printf("Reached last camera. Rewinding...\n");
            while(scene->cam->prev != NULL)
                scene->cam = scene->cam->prev;
        }
        create_img(scene);
    }
    else
        printf("Only one camera exists in the scene\n");
}

int     sphere_man()
{
    system("clear");
    printf(BCYN"SPHERE :\n\tW - Move Up\n\t");
    printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
    printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards\n\t");
    printf("+ (NumPad) - Increase Diameter\n\t- (NumPad) - Decrease Diameter");
    printf("\nQ - Exit this mode");
    printf(BBLU"\nPress ESC or click the close button on the window to exit\n"reset);
}

void    sphere_manip()
{
    sphere_man();
}

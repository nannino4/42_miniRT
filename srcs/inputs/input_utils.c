#include "header.h"
#include "ANSI-color-codes.h"

int	exit_func(void *param)
{
	if (param == NULL)
		printf(BRED"EXITING\n"reset);
	exit(0);
	return (0);
}

void	camera_wheel(t_scene *scene)
{
    if(scene->cam->next !=NULL || scene->cam->prev != NULL)
    {
        if(scene->cam->next != NULL)
        {
            printf(YEL"Switching Camera\n"reset);
            scene->cam = scene->cam->next;
        }
        else
        {
            printf(YEL"Reached last camera. Rewinding...\n"reset);
            while(scene->cam->prev != NULL)
                scene->cam = scene->cam->prev;
        }
        create_img(scene);
    }
    else
        printf(YEL"Only one camera exists in the scene\n"reset);
}

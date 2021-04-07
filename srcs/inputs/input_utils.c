#include "header.h"
#include "ANSI-color-codes.h"

int	exit_func(void *param)
{
	if (param == NULL)
		printf(BRED"EXITING\n"reset);
	exit(0);
	return (0);
}

void	light_wheel(t_scene *scene)
{
    if(scene->selected_light->next != NULL || scene->selected_light->prev != NULL)
    {
        if(scene->selected_light->next != NULL)
        {
            printf("Switching selected Light\n");
            scene->selected_light = scene->selected_light->next;
        }
        else
        {
            printf("Reached last Light. Rewinding...\n");
            while(scene->selected_light->prev != NULL)
                scene->selected_light = scene->selected_light->prev;
        }
    }
    else
        printf("Only one Light exists in the scene\n");
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

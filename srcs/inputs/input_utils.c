#include "header.h"

int	exit_func(t_scene *scene)
{
	printf(BRED"EXITING\n"reset);
    free_all(scene);  
	exit(0);
	return (0);
}

void	light_wheel(t_scene *scene)
{
    if(scene->selected_light->next != NULL || scene->selected_light->prev != NULL)
    {
        if(scene->selected_light->next != NULL)
        {
            printf(YEL"Switching to the next Light\n"reset);
            scene->selected_light = scene->selected_light->next;
        }
        else
        {
            printf(YEL"Reached last Light. Rewinding...\n"reset);
            while(scene->selected_light->prev != NULL)
                scene->selected_light = scene->selected_light->prev;
        }
    }
    else
        printf(YEL"Only one Light exists in the scene\n"reset);
}

void	camera_wheel(t_scene *scene)
{
    if(scene->cam->next !=NULL || scene->cam->prev != NULL)
    {
        if(scene->cam->next != NULL)
        {
            printf(YEL"Switching to the next Camera\n"reset);
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

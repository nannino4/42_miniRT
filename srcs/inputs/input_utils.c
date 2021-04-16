#include "header.h"

int	exit_func(t_scene *scene)
{
	printf(BRED"EXITING\n"RESET);
	free_all(scene);
	exit(0);
	return (0);
}

void	light_wheel(t_scene *scene)
{
	if (scene->selected_light->next != NULL || \
			scene->selected_light->prev != NULL)
	{
		if (scene->selected_light->next != NULL)
		{
			printf(YEL"Switching to the next Light\n"RESET);
			scene->selected_light = scene->selected_light->next;
		}
		else
		{
			printf(YEL"Reached last Light. Rewinding...\n"RESET);
			while (scene->selected_light->prev != NULL)
				scene->selected_light = scene->selected_light->prev;
		}
	}
	else
		printf(YEL"Only one Light exists in the scene\n"RESET);
}

void	camera_wheel(t_scene *scene)
{
	if (scene->cam->next != NULL || scene->cam->prev != NULL)
	{
		if (scene->cam->next != NULL)
		{
			printf(YEL"Switching to the next Camera\n"RESET);
			scene->cam = scene->cam->next;
		}
		else
		{
			printf(YEL"Reached last camera. Rewinding...\n"RESET);
			while (scene->cam->prev != NULL)
				scene->cam = scene->cam->prev;
		}
		scene->threading(scene);
	}
	else
		printf(YEL"Only one camera exists in the scene\n"RESET);
}

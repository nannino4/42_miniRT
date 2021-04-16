#include "header.h"

void	free_objects(t_obj *obj)
{
	t_obj	*temp;

	temp = obj;
	while (temp)
	{
		obj = obj->next;
		if (temp->obj)
		{
			free(temp->obj);
			temp->obj = 0;
		}
		temp->next = 0;
		free(temp);
		temp = obj;
	}
}

void	free_camera(t_cam *cam)
{
	t_cam	*temp;

	temp = cam;
	while (temp)
	{
		cam = cam->next;
		temp->next = 0;
		free(temp);
		temp = cam;
	}
}

void	free_lights(t_light *light)
{
	t_light	*temp;

	temp = light;
	while (temp)
	{
		light = light->next;
		temp->next = 0;
		free(temp);
		temp = light;
	}
}

void	free_all(t_scene *scene)
{
	free_objects(scene->obj);
	free_camera(scene->cam);
	free_lights(scene->light);
}

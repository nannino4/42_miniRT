#include "header.h"

t_obj	*select_obj(t_scene *scene, int x, int y)
{
	double	min_distance;
	t_obj	*obj_list;
	t_obj	*intersected_obj;
    t_ray   ray;

	intersected_obj = 0;
	min_distance = MAX_DISTANCE;
	obj_list = scene->obj;
    create_ray(scene, &ray, x, y);
	while (obj_list)
	{
		ray.intersection.distance = MAX_DISTANCE;
		intersect_obj(obj_list, ray);
		if (ray.intersection.distance < min_distance)
		{
			min_distance = ray.intersection.distance;
			intersected_obj = obj_list;
		}
		obj_list = obj_list->next;
	}
    return (intersected_obj);
}

int     exit_func(void *param)
{
    if(param == NULL)
        printf("EXITING\n");
    exit(0);
    return (0);
}

void    camera_wheel(t_scene *scene)
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
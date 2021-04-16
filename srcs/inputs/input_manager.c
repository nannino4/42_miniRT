#include "header.h"

int	keyboard_input(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (key == ESC_KEY)
		exit_func(scene);
	else if (key == C_KEY)
		camera_wheel(scene);
	else if (key == PG_UP_KEY || key == PG_DOWN_KEY || key == ARROW_DX_KEY || \
			key == ARROW_DOWN_KEY || key == ARROW_UP_KEY || key == A_KEY || \
			key == S_KEY || key == D_KEY || key == ARROW_SX_KEY || key == W_KEY)
	{
		transform_camera(scene->cam, key);
		scene->threading(scene);
	}
	else if (key == L_KEY)
		select_light(scene);
	else
		printf(YEL "Invalid key pressed...\n" RESET);
	return (key);
}

int	mouse_input_2(int button, int x, int y, t_scene *scene)
{
	t_p	center;
	t_p	click;
	t_v	direction;
	t_v	axis;

	if (button == 2)
	{
		center = create_v((double)scene->w / 2.0, (double)scene->h / 2.0, 0);
		click = create_v(x, (double)scene->h - y, 0);
		direction = v_normalize(v_sub(click, center));
		direction = v_normalize(v_sum(v_scalar_mul(scene->cam->up, \
				direction.y), v_scalar_mul(scene->cam->dx, direction.x)));
		axis = v_normalize(v_cross_prod(scene->cam->direction, direction));
		rot_camera(scene->cam, axis);
		scene->threading(scene);
	}
	else if (button != 1)
		printf(YEL"Invalid mouse click\n"RESET);
	return (1);
}

int	mouse_input(int button, int x, int y, void *param)
{
	t_scene	*scene;
	t_ray	ray;

	scene = (t_scene *)param;
	if (button == 1)
	{
		create_ray(scene, &ray, (double)x + 0.5, (double)y + 0.5);
		find_intersection(&ray, scene);
		if (ray.intersection.distance < MAX_DISTANCE)
		{
			if (ray.intersection.intersected_obj->id == SPHERE)
				select_sphere(scene, ray.intersection.intersected_obj);
			else if (ray.intersection.intersected_obj->id == PLANE)
				select_plane(scene, ray.intersection.intersected_obj);
			else if (ray.intersection.intersected_obj->id == CYLINDER)
				select_cylinder(scene, ray.intersection.intersected_obj);
			else if (ray.intersection.intersected_obj->id == TRIANGLE)
				select_triangle(scene, ray.intersection.intersected_obj);
			else if (ray.intersection.intersected_obj->id == SQUARE)
				select_square(scene, ray.intersection.intersected_obj);
		}
		else
			printf(YEL"No object where clicked\n"RESET);
	}
	return (mouse_input_2(button, x, y, scene));
}

void	main_info(void)
{
	system("clear");
	printf(\
			BMAG"CAMERA SELECTED :\n\n"\
			BBLU"⇞(Pg Up)"HBLU"\tMove Forwards\n"\
			BBLU"⇟(Pg Down)"HBLU"\tMove Backwards\n\n"\
			BBLU"\tW"HBLU"\tMove Up\n"\
			BBLU"\tS"HBLU"\tMove Down\n"\
			BBLU"\tA"HBLU"\tMove Left\n"\
			BBLU"\tD"HBLU"\tMove Right\n\n"\
			BBLU"\t◀-"HBLU"\tRotate Left\n"\
			BBLU"\t-▶"HBLU"\tRotate Right\n"\
			BBLU"\t⬇"HBLU"\tRotate down\n"\
			BBLU"\t⬆"HBLU"\tRotate Up\n\n"\
			BBLU"\t\tOR\n\n"\
			"\t"BBLU"RMB\tRight Click in the direction the camera "
			"should turn"RESET"\n\n"\
			BCYN"\tC"HCYN"\tCycle cameras\n"\
			BCYN"\tL"HCYN"\tCycle Lights\n\t"\
			BCYN"LMB"HCYN"\tLeft Click any object to enter it's "
			"manipulation mode\n\n"\
			YEL"Press "BHYEL"ESC"YEL" or click the close button on "
			"the view window to"\
			" exit\n"UGRN"\n-------------------------------------------------"\
			"-----------------\n\n"RESET);
}

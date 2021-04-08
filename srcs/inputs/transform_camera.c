#include "header.h"

void	move_camera(t_cam *cam, t_v axis)
{
	cam->origin = v_sum(cam->origin, v_scalar_mul(axis, MOVE_EPSILON));
}

void	rot_camera(t_cam *cam, t_v axis)
{
	cam->direction = v_normalize(rotate_vector(cam->direction, axis,
				ROT_EPSILON));
	cam->up = v_normalize(rotate_vector(cam->up, axis, ROT_EPSILON));
	cam->dx = v_normalize(rotate_vector(cam->dx, axis, ROT_EPSILON));
}

void	transform_camera(t_cam *cam, int key)
{
	if (key == PG_UP_KEY)
		move_camera(cam, cam->direction);
	else if (key == PG_DOWN_KEY)
		move_camera(cam, v_scalar_mul(cam->direction, -1));
	else if (key == W_KEY)
		move_camera(cam, cam->up);
	else if (key == S_KEY)
		move_camera(cam, v_scalar_mul(cam->up, -1));
	else if (key == D_KEY)
		move_camera(cam, cam->dx);
	else if (key == A_KEY)
		move_camera(cam, v_scalar_mul(cam->dx, -1));
	else if (key == ARROW_UP_KEY)
		rot_camera(cam, cam->dx);
	else if (key == ARROW_DOWN_KEY)
		rot_camera(cam, v_scalar_mul(cam->dx, -1));
	else if (key == ARROW_DX_KEY)
		rot_camera(cam, v_scalar_mul(cam->up, -1));
	else
		rot_camera(cam, cam->up);
}

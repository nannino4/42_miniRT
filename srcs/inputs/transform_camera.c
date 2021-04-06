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
	if (key == MOVE_FORWARD)
		move_camera(cam, cam->direction);
	if (key == MOVE_BACK)
		move_camera(cam, v_scalar_mul(cam->direction, -1));
	if (key == MOVE_DOWN)
		move_camera(cam, v_scalar_mul(cam->up, -1));
	if (key == MOVE_DX)
		move_camera(cam, cam->dx);
	if (key == MOVE_SX)
		move_camera(cam, v_scalar_mul(cam->dx, -1));
	if (key == ROT_UP)
		rot_camera(cam, cam->dx);
	if (key == ROT_DOWN)
		rot_camera(cam, v_scalar_mul(cam->dx, -1));
	if (key == ROT_DX)
		rot_camera(cam, v_scalar_mul(cam->up, -1));
	if (key == ROT_SX)
		rot_camera(cam, cam->up);
}

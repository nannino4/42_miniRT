#include "header.h"

void	set_camera_orientation(t_cam *cam)
{
	if (is_equal(v_dot_prod(cam->direction, create_v(0, 1, 0)), 0))
		cam->up = create_v(0, 1, 0);
	else if(is_equal(v_norm(v_cross_prod(cam->direction, create_v(0, 1, 0))), 0))
		cam->up = create_v(1, 0, 0);
	else
	{
		cam->up = v_normalize(v_sub(project_p_to_plane(v_sum(cam->origin, create_v(0, 1, 0)), cam->origin, cam->direction), cam->origin));
		if(is_greater(0, v_dot_prod(cam->up, create_v(0, 1, 0))))
			cam->up = v_scalar_mul(cam->up, -1);
	}
	cam->dx = v_normalize(v_cross_prod(cam->direction, cam->up));
}

void	set_square_orientation(t_square *square)
{
	t_p	p1;

	if (is_equal(v_dot_prod(square->n, create_v(0, 1, 0)), 0))
		square->up = create_v(0, 1, 0);
	else if(is_equal(v_norm(v_cross_prod(square->n, create_v(0, 1, 0))), 0))
		square->up = create_v(1, 0, 0);
	else
	{
		p1 = project_p_to_plane(v_sum(square->c, create_v(0, 1, 0)), square->c, square->n);
		square->up = v_normalize(v_sub(p1, square->c));
		if(is_greater(0, v_dot_prod(square->up, create_v(0, 1, 0))))
			square->up = v_scalar_mul(square->up, -1);
	}
	square->dx = v_normalize(v_cross_prod(square->n, square->up));
}

void	set_cylinder_orientation(t_cyl *cylinder)
{
	t_p		p;

	if (is_equal(v_dot_prod(cylinder->n, create_v(0, 1, 0)), 0))
		cylinder->up = create_v(0, 1, 0);
	else if(is_equal(v_norm(v_cross_prod(cylinder->n, create_v(0, 1, 0))), 0))
		cylinder->up = create_v(1, 0, 0);
	else
	{
		p = project_p_to_plane(v_sum(cylinder->c, create_v(0, 1, 0)), cylinder->c, cylinder->n);
		cylinder->up = v_normalize(v_sub(p, cylinder->c));
	}
	cylinder->dx = v_normalize(v_cross_prod(cylinder->n, cylinder->up));
	cylinder->c_up = v_dot_prod(cylinder->c, cylinder->up);
	cylinder->c_dx = v_dot_prod(cylinder->c, cylinder->dx);
}

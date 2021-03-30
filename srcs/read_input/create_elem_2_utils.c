#include "header.h"

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
		scene->screen.up = create_v(1, 0, 0);
	else
	{
		p = project_p_to_plane(v_sum(cylinder->c, create_v(0, 1, 0)), cylinder->c, cylinder->n);
		cylinder->up = v_normalize(v_sub(p, cylinder->c));
	}
	cylinder->dx = v_normalize(v_cross_prod(cylinder->n, cylinder->up));
}

#include "header.h"

void	move_square(void *param, t_v axis)
{
	t_square	*square;

	square = (t_square *)param;
	square->c = v_sum(square->c, v_scalar_mul(axis, MOVE_EPSILON));
}

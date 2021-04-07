#include "header.h"

t_v	v_scalar_mul(t_v v, double a)
{
	v.x *= a;
	v.y *= a;
	v.z *= a;
	return (v);
}

double	v_dot_prod(t_v v1, t_v v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

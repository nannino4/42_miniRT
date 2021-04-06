#include "header.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int trgb)
{
	char	*dst;

	dst = img->addr + (y * img->line_l + x * (img->bpp / 8));
	*(int *)dst = trgb;
}

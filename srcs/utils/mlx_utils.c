#include "header.h"

void        my_mlx_pixel_put(t_scene scene, int x, int y, int trgb)
{
    char    *dst;

    dst = scene.addr + (y * scene.line_l + x * (scene.bbp / 8));
    *(int*)dst = trgb;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 09:56:18 by gcefalo           #+#    #+#             */
/*   Updated: 2021/02/17 13:08:02 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_square(t_data *data, int l, int color)
{
	int		x;
	int		y;

	x = 0;
	y = data->y - (l / 2);
	while (x < l)
		my_mlx_pixel_put(data, data->x - (l / 2) + x++, y, color);
	x = 0;
	y = data->y + (l / 2);
	while (x < l)
		my_mlx_pixel_put(data, data->x - (l / 2) + x++, y, color);
	y = 0;
	x = data->x - (l / 2);
	while (y < l)
		my_mlx_pixel_put(data, x, data->y - (l / 2) + y++, color);
	y = 0;
	x = data->x + (l / 2);
	while (y < l)
		my_mlx_pixel_put(data, x, data->y - (l / 2) + y++, color);
}

void	print_circle(t_data *data, int d, int color)
{
	int		x;
	int		y;

	x = data->x - (d / 2);
	while (x < data->x + (d / 2))
	{
		y = data->y + sqrt((d / 2) * (d / 2) - (x - data->x) * (x - data->x));
		my_mlx_pixel_put(data, x, y, color);
		y = data->y - sqrt((d / 2) * (d / 2) - (x - data->x) * (x - data->x));
		my_mlx_pixel_put(data, x, y, color);
		x++;
	}
	y = data->y - (d / 2);
	while (y < data->y + (d / 2))
	{
		x = data->x + sqrt((d / 2) * (d / 2) - (y - data->y) * (y - data->y));
		my_mlx_pixel_put(data, x, y, color);
		x = data->x - sqrt((d / 2) * (d / 2) - (y - data->y) * (y - data->y));
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

//void	print_triangle(t_data *data, t_vert vertix, int color)
//{
//}

int		main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	data;
//	t_vert	vertix;

	data.x = WIDTH / 2;
	data.y = HEIGHT / 2;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "JohnnyBoy");
	data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length, \
			&data.endian);
	print_square(&data, HEIGHT / 4, 0x00FF0000);
	print_circle(&data, HEIGHT / 4, 0x0000FF00);
//	print_triangle(&data, vertix, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, data.img, 0, 0);
	mlx_loop(mlx);
}

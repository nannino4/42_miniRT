#include "header.h"

void	write_file(unsigned char header[], unsigned char *buf,
					unsigned int size)
{
	int	fd;

	fd = open("./screenshot.bmp", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	write(fd, header, 54);
	write(fd, (char *)buf, size);
	close(fd);
}

void	set_pixels(unsigned char *buf, t_scene *scene, int width_in_bytes)
{
	int				i;
	int				j;
	int				tmp;

	tmp = scene->h;
	i = -1;
	while (++i < scene->h)
	{
		j = -1;
		--tmp;
		while (++j < scene->w)
		{
			buf[tmp * width_in_bytes + j * 3 + 0] = \
				(*((unsigned int *)(scene->img.addr + (i * scene->img.line_l \
				 + j * (scene->img.bpp / 8))))) & 0xff;
			buf[tmp * width_in_bytes + j * 3 + 1] = \
				((*((unsigned int *)(scene->img.addr + (i * scene->img.line_l \
				 + j * (scene->img.bpp / 8))))) >> 8) & 0xff;
			buf[tmp * width_in_bytes + j * 3 + 2] = \
				((*((unsigned int *)(scene->img.addr + (i * scene->img.line_l \
				 + j * (scene->img.bpp / 8))))) >> 16) & 0xff;
		}
	}
}

void	save_image_to_bmp_file(t_scene *scene)
{
	t_bmp	data;

	data.width_in_bytes = ((scene->w * 24 + 31) / 32) * 4;
	data.imagesize = data.width_in_bytes * scene->h;
	data.offset = 54;
	data.filesize = data.offset + data.imagesize;
	data.header_size = 40;
	data.planes_n = 1;
	data.bpp = 24;
	ft_bzero(data.header, 54);
	ft_memcpy(data.header, "BM", 2);
	ft_memcpy(data.header + 2, &data.filesize, 4);
	ft_memcpy(data.header + 10, &data.offset, 4);
	ft_memcpy(data.header + 14, &data.header_size, 4);
	ft_memcpy(data.header + 18, &scene->w, 4);
	ft_memcpy(data.header + 22, &scene->h, 4);
	ft_memcpy(data.header + 26, &data.planes_n, 2);
	ft_memcpy(data.header + 28, &data.bpp, 2);
	ft_memcpy(data.header + 34, &data.imagesize, 4);
	data.buf = malloc(data.imagesize);
	set_pixels(data.buf, scene, data.width_in_bytes);
	write_file(data.header, data.buf, data.imagesize);
	free(data.buf);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int trgb)
{
	char	*dst;

	dst = img->addr + (y * img->line_l + x * (img->bpp / 8));
	*(int *)dst = trgb;
}

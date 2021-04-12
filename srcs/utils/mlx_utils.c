#include "header.h"

void	write_file(unsigned char header[], unsigned char *buf,
					unsigned int size)
{
	int fd;

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
			buf[tmp * width_in_bytes + j * 3 + 0] =
				(*((unsigned int*)(scene->img.addr + (i * scene->img.line_l +
				j * (scene->img.bpp / 8))))) & 0xff;
			buf[tmp * width_in_bytes + j * 3 + 1] =
				((*((unsigned int*)(scene->img.addr + (i * scene->img.line_l +
				j * (scene->img.bpp / 8))))) >> 8) & 0xff;
			buf[tmp * width_in_bytes + j * 3 + 2] =
				((*((unsigned int*)(scene->img.addr + (i * scene->img.line_l +
				j * (scene->img.bpp / 8))))) >> 16) & 0xff;
		}
	}
}

void	save_image_to_bmp_file(t_scene *scene)
{
	unsigned char	header[54];
	unsigned char	*buf;
	unsigned int	width_in_bytes;
	unsigned int	imagesize;
	unsigned int	filesize;

	width_in_bytes = ((scene->w * 24 + 31) / 32) * 4;
	imagesize = width_in_bytes * scene->h;
	filesize = 54 + imagesize;
	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &filesize, 4);
	ft_memcpy(header + 10, "54", 4);
	ft_memcpy(header + 14, "40", 4);
	ft_memcpy(header + 18, &scene->w, 4);
	ft_memcpy(header + 22, &scene->h, 4);
	ft_memcpy(header + 26, "1", 2);
	ft_memcpy(header + 28, "24", 2);
	ft_memcpy(header + 34, &imagesize, 4);
	buf = malloc(imagesize);
	set_pixels(buf, scene, width_in_bytes);
	write_file(header, buf, imagesize);
	free(buf);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int trgb)
{
	char	*dst;

	dst = img->addr + (y * img->line_l + x * (img->bpp / 8));
	*(int *)dst = trgb;
}

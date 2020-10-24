/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:43:43 by gicho             #+#    #+#             */
/*   Updated: 2020/10/24 12:43:43 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fileio.h"

void	set_default_value(unsigned char header[])
{
	unsigned int	bi_size;
	unsigned int	bf_off_bits;
	unsigned short	bi_planes;

	bi_size = 40;
	bf_off_bits = 54;
	bi_planes = 1;
	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 10, &bf_off_bits, 4);
	ft_memcpy(header + 14, &bi_size, 4);
	ft_memcpy(header + 26, &bi_planes, 2);
}

void	set_header(unsigned char header[], int width,
				int height, int width_in_bytes)
{
	unsigned short	bitcount;
	unsigned int	imagesize;
	unsigned int	filesize;

	bitcount = 24;
	imagesize = width_in_bytes * height;
	filesize = 54 + imagesize;
	set_default_value(header);
	ft_memcpy(header + 2, &filesize, 4);
	ft_memcpy(header + 18, &width, 4);
	ft_memcpy(header + 22, &height, 4);
	ft_memcpy(header + 28, &bitcount, 2);
	ft_memcpy(header + 34, &imagesize, 4);
}

void	set_pixels(unsigned char *buf, int **data, int width, int height)
{
	unsigned int	width_in_bytes;
	int				i;
	int				j;
	int				tmp;

	width_in_bytes = ((width * 24 + 31) / 32) * 4;
	tmp = height;
	i = -1;
	while (++i < height)
	{
		j = -1;
		--tmp;
		while (++j < width)
		{
			buf[tmp * width_in_bytes + j * 3 + 0] = (data[i][j]) & 0xff;
			buf[tmp * width_in_bytes + j * 3 + 1] = (data[i][j] >> 8) & 0xff;
			buf[tmp * width_in_bytes + j * 3 + 2] = (data[i][j] >> 16) & 0xff;
		}
	}
}

void	write_file(unsigned char header[], unsigned char *buf,
					unsigned int size)
{
	int fd;

	fd = open("./screenshot.bmp", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	write(fd, header, 54);
	write(fd, (char*)buf, size);
	close(fd);
}

int		save_image_to_bmp_file(int **data, int width, int height)
{
	unsigned char	header[54];
	unsigned char	*buf;
	unsigned int	width_in_bytes;
	unsigned int	imagesize;

	width_in_bytes = ((width * 24 + 31) / 32) * 4;
	imagesize = width_in_bytes * height;
	set_header(header, width, height, width_in_bytes);
	if (!(buf = malloc(imagesize)))
		return (0);
	set_pixels(buf, data, width, height);
	write_file(header, buf, imagesize);
	free(buf);
	return (1);
}

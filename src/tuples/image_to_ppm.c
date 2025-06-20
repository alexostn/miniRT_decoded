/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_to_ppm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:08:59 by oostapen          #+#    #+#             */
/*   Updated: 2025/06/20 00:46:16 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include <math.h>

// place it to ft_libft prototype :
// static void	ft_itoa_buf(int n, char *buf)
// {
// 	if (n > 99)
// 		ft_strlcpy(buf, (char[]){n / 100 + '0', (n / 10 % 10) + '0', n % 10 + '0', 0}, 4);
// 	else if (n > 9)
// 		ft_strlcpy(buf, (char[]){n / 10 + '0', n % 10 + '0', 0}, 4);
// 	else
// 		ft_strlcpy(buf, (char[]){n + '0', 0}, 2);
// }

static void	append_color_string(char *line, int *line_len, int channel, int fd)
{
	char	num[4];
	int		num_len;

	ft_itoa_buf(channel, num);
	num_len = ft_strlen(num);
	if (*line_len + num_len + 1 > 70 && *line_len > 0)
	{
		ft_putendl_fd(line, fd);
		ft_bzero(line, 71);
		*line_len = 0;
	}
	if (*line_len > 0)
	{
		ft_strlcat(line, " ", 71);
		(*line_len)++;
	}
	ft_strlcat(line, num, 71);
	*line_len += num_len;
}

// static void	append_to_line(char **line, int *line_len, const char *str, int fd)
// {
// 	int	str_len;

// 	str_len = ft_strlen(str);
// 	if (*line_len + str_len > 70)
// 	{
// 		ft_putendl_fd(*line, fd);
// 		ft_bzero(*line, 71);
// 		*line_len = 0;
// 	}
// 	ft_strlcat(*line, str, 71);
// 	*line_len += str_len;
// }

static void	write_pixel_data(t_image *img, int fd)
{
	char	line[71];
	int		line_len;
	t_color	c;
	int		x;
	int		y;

	ft_bzero(line, 71);
	line_len = 0;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			c = read_pixel(img, x, y);
			append_color_string(line, &line_len, clamp_channel(c.r), fd);
			append_color_string(line, &line_len, clamp_channel(c.g), fd);
			append_color_string(line, &line_len, clamp_channel(c.b), fd);
		}
		if (line_len > 0)
			ft_putendl_fd(line, fd);
		ft_bzero(line, 71);
		line_len = 0;
	}
}

// use libft: ft_putstr_fd, ft_putendl_fd, ft_putnbr_fd
// 1. Writing the "magic number" P3
// 2. Writing width and height on one line
// 3. Writing the maximum color value
// Next will follow the code for writing pixel data...

void	image_to_ppm(t_image *image, int fd)
{
	ft_putendl_fd("P3", fd);
	ft_putnbr_fd(image->width, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(image->height, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("255", fd);
	write_pixel_data(image, fd);
}

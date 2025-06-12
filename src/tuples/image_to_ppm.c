/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_to_ppm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:08:59 by oostapen          #+#    #+#             */
/*   Updated: 2025/06/12 22:19:12 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include <math.h>

/////////////////// PPM SET /////////////////////////
static void	write_ppm_pixels(t_image *image, int fd)
{
	int		y;
	int		x;
	t_color	color;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			color = read_pixel(image, x, y);
			ft_putnbr_fd(clamp_channel(color.r), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(clamp_channel(color.g), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(clamp_channel(color.b), fd);
			if (x < image->width - 1)
				ft_putchar_fd(' ', fd);
			x++;
		}
		ft_putchar_fd('\n', fd);
		y++;
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
	write_ppm_pixels(image, fd);
}

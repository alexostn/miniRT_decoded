/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/09 22:09:11 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "image.h"
#include <math.h> //for fmin or own clamp_value()
#include <stdint.h> // for uint32_t 32-bit crossplatfomed

/*
** write_pixel()
** Writes a pixel in ARGB format (0xAARRGGBB)
*/
void	write_pixel(t_image *img, int x, int y, t_color_format cf)
{
	char		*dst;
	uint32_t	pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = color_to_mlx(&cf.color, cf.format);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(uint32_t *)dst = pixel;
}

/*
** read_pixel()
** Reads a pixel in ARGB format (0xAARRGGBB) - FIXED VERSION
** Memory layout (little-endian): [B, G, R, A]
** uint32_t value: 0xAARRGGBB
*/
t_color	read_pixel(t_image *img, int x, int y)
{
	t_color		color;
	uint32_t	*pixel;
	uint32_t	argb;

	color = (t_color){0.0, 0.0, 0.0, 0.0};
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (color);
	pixel = (uint32_t *)(img->addr
			+ (y * img->line_length + x * (img->bits_per_pixel / 8)));
	argb = *pixel;
	color.a = ((argb >> 24) & 0xFF) / 255.0;
	color.r = ((argb >> 16) & 0xFF) / 255.0;
	color.g = ((argb >> 8) & 0xFF) / 255.0;
	color.b = (argb & 0xFF) / 255.0;
	return (color);
}

// /*
// bits_per_pixel / 8
// Convert bits per pixel to bytes per pixel (8 bits = 1 byte)
// Used to calculate the correct memory offset for each pixel
// when writing to or reading from the image buffer

// Use (int)(r * 255 + 0.5) for proper rounding instead of truncating
// */

// void	write_pixel(t_image *img, int x, int y, t_color_format cf)
// {
// 	char		*dst;
// 	uint32_t	pixel;

// 	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
// 		return ;
// 	pixel = color_to_mlx(&cf.color, cf.format);
// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	*(uint32_t *)dst = pixel;
// }

// /*
// | 31–24 (Red) | 23–16 (Green) | 15–8 (Blue) | 7–0 (Alpha) |
// |    0xFF     |      0x00     |    0x00     |    0xFF     |
// The alpha channel remains in the least significant 8 bits (positions 0-7)
// */
// t_color	read_pixel(t_image *img, int x, int y)
// {
// 	t_color		color;
// 	uint32_t	*pixel;
// 	uint32_t	rgba;

// 	color = (t_color){0.0, 0.0, 0.0, 0.0};
// 	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
// 		return (color);
// 	pixel = (uint32_t *)(img->addr
// 			+ (y * img->line_length + x * (img->bits_per_pixel / 8)));
// 	rgba = *pixel;
// 	color.r = ((rgba >> 24) & 0xFF) / 255.0;
// 	color.g = ((rgba >> 16) & 0xFF) / 255.0;
// 	color.b = ((rgba >> 8) & 0xFF) / 255.0;
// 	color.a = (rgba & 0xFF) / 255.0;
// 	return (color);
// }

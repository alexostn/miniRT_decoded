/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:49:28 by oostapen          #+#    #+#             */
/*   Updated: 2025/06/06 00:31:11 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "tuples.h"
# include "image.h"
# include <stdint.h>

/*** Color type (separate from vector): ***/
typedef struct s_color
{
	double	r; // [0.0, 1.0]
	double	g;
	double	b;
	double	a; // alpha channel (1.0 = opaque or solid)
}	t_color;

/*** Supported color formats (byte order in uint32_t): ***/
typedef enum e_format
{
	FORMAT_ARGB,
	FORMAT_RGBA,
	FORMAT_BGRA,
	FORMAT_ABGR
}	t_format;

/***Color format ***/
typedef struct s_color_format
{
	t_color		color;
	t_format	format;
}	t_color_format;

/*** Color creation and conversion: ***/
// Returns a color tuple with components in [0.0, 1.0]
t_tuple		color_d(double r, double g, double b);
t_color		tuple_to_color(t_tuple tuple);
t_tuple		color_to_tuple(t_color color);

/*** Convert color to uint32_t in the required format: ***/
uint32_t	color_to_mlx(t_color *c, t_format fmt);

/*** Pixel write and read: ***/
void		write_pixel(t_image *img, int x, int y, t_color_format cf);
t_color		read_pixel(t_image *img, int x, int y);

#endif

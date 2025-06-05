/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_converters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:44:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/06/06 00:21:21 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include <math.h>

t_color	tuple_to_color(t_tuple tuple)
{
	return ((t_color){tuple.x, tuple.y, tuple.z, 0.0});
}

t_tuple	color_to_tuple(t_color color)
{
	return (tuple(color.r, color.g, color.b, color.a));
}

static uint8_t	clamp_channel(double value)
{
	if (value < 0.0)
		value = 0.0;
	else if (value > 1.0)
		value = 1.0;
	return ((uint8_t)(value * 255.0 + 0.5));
}

uint32_t	color_to_mlx(t_color *c, t_format fmt)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = clamp_channel(c->r);
	g = clamp_channel(c->g);
	b = clamp_channel(c->b);
	a = clamp_channel(c->a);
	if (fmt == FORMAT_ARGB)
		return ((a << 24) | (r << 16) | (g << 8) | b);
	else if (fmt == FORMAT_RGBA)
		return ((r << 24) | (g << 16) | (b << 8) | a);
	else if (fmt == FORMAT_BGRA)
		return ((b << 24) | (g << 16) | (r << 8) | a);
	else if (fmt == FORMAT_ABGR)
		return ((a << 24) | (b << 16) | (g << 8) | r);
	return (0);
}

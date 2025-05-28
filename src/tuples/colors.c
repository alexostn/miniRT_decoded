/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:22:57 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/28 20:21:34 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

// for book tests where we receive data in range: 0 - 1
t_tuple	color_d(double r, double g, double b)
{
	return (tuple(r, g, b, 0.0));
}

// TODO:
// Creates a color tuple:converted_color.x = r / 255.0;
// for project , as we receive in range : 0 - 255
// t_tuple	color_c(double r, double g, double b)
// {
// 	t_tuple	converted_color;

// 	converted_color.x = r / 255.0;
// 	converted_color.y = g / 255.0;
// 	converted_color.z = b / 255.0;
// 	converted_color.w = 0.0;
// 	return (converted_color);
// }

// TODO:
// #include <math.h> (is in tuples.h)
// For round(), if you plan to round here, or for fmin/fmax if available.
// Alternatively,for clarity, clamping implemented manually:
// static double	clamp_value(double val, double min_val, double max_val)
// {
// 	if (val < min_val)
// 		return (min_val);
// 	if (val > max_val)
// 		return (max_val);
// 	return (val);
// }

// TODO:
// For rounding before saving, if t_tuple stored rounded doubles:
// scaled_color.x = round(clamp_value(r_scaled, 0.0, 255.0));
// But usually t_tuple.x/y/z remain double,
// TODO:
// and round() and (int) are applied later.
// t_tuple	color_to_rgb255_scaled(double r_norm, double g_norm, double b_norm)
// {
// 	t_tuple	scaled_color;
// 	double	r_scaled;
// 	double	g_scaled;
// 	double	b_scaled;

// 	r_scaled = r_norm * 255.0;
// 	g_scaled = g_norm * 255.0;
// 	b_scaled = b_norm * 255.0;
// 	scaled_color.x = clamp_value(r_scaled, 0.0, 255.0);
// 	scaled_color.y = clamp_value(g_scaled, 0.0, 255.0);
// 	scaled_color.z = clamp_value(b_scaled, 0.0, 255.0);
// 	scaled_color.w = 0.0;
// 	return (scaled_color);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:30:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 23:28:43 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static double	normalize_color_value(int val)
{
	if (val < 0)
		return (0.0);
	if (val > 255)
		return (1.0);
	return (val / 255.0);
}

t_tuple	parse_color_rgb(char **str)
{
	int		r;
	int		g;
	int		b;
	t_tuple	error;

	error = (t_tuple){0, 0, 0, -1.0};
	r = (int)parse_double(str);
	if (**str != ',')
		return (error);
	(*str)++;
	g = (int)parse_double(str);
	if (**str != ',')
		return (error);
	(*str)++;
	b = (int)parse_double(str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (error);
	return (color_d(normalize_color_value(r),
			normalize_color_value(g),
			normalize_color_value(b)));
}

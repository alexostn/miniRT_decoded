/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 22:48:39 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "colors.h"// for clamp_channel

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 22:27:00 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "colors.h"
#include "libft.h"

double	parse_double(char **str)
{
	double	result;
	int		sign;
	double	fraction;
	double	divisor;

	sign = 1;
	result = 0.0;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		fraction = 0.0;
		divisor = 10.0;
		while (**str >= '0' && **str <= '9')
		{
			fraction += (**str - '0') / divisor;
			divisor *= 10.0;
			(*str)++;
		}
		result += fraction;
	}
	return (result * sign);
}

t_tuple	parse_vector3(char **str)
{
	double	x;
	double	y;
	double	z;

	x = parse_double(str);
	if (**str == ',')
		(*str)++;
	y = parse_double(str);
	if (**str == ',')
		(*str)++;
	z = parse_double(str);
	return (vector(x, y, z));
}

t_tuple	parse_color_rgb(char **str)
{
	double	r;
	double	g;
	double	b;

	r = parse_double(str);
	if (**str == ',')
		(*str)++;
	g = parse_double(str);
	if (**str == ',')
		(*str)++;
	b = parse_double(str);

	return (color_d(normalize_rgb_channel(r),
			normalize_rgb_channel(g),
			normalize_rgb_channel(b)));
}

/*
// Use your normalize_rgb_channel for each component
or
// Normalize 0-255 to 0-1 and use your color_d()
return (color_d(r / 255.0, g / 255.0, b / 255.0));
or "math_utils.h"
r = clamp_double(r, 0.0, 255.0) / 255.0;
g = clamp_double(g, 0.0, 255.0) / 255.0;
b = clamp_double(b, 0.0, 255.0) / 255.0;
return (color_d(r, g, b));
*/

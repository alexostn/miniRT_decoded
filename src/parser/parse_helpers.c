/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 23:58:59 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "colors.h"

static double	parse_fraction(char **str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (**str >= '0' && **str <= '9')
	{
		fraction += (**str - '0') / divisor;
		divisor *= 10.0;
		(*str)++;
	}
	return (fraction);
}

double	parse_double(char **str)
{
	double	result;
	int		sign;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		result += parse_fraction(str);
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

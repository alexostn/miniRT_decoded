/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:21:56 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 22:21:58 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** skip_whitespace - Skip spaces and tabs
*/
static void	skip_whitespace(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

/*
** parse_double - Parse next floating point number
*/
double	parse_double(char **str)
{
	double	result;
	int		sign;
	double	fraction;
	double	divisor;

	skip_whitespace(str);
	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	result = 0.0;
	while (**str >= '0' && **str <= '9')
		result = result * 10.0 + (*(*str)++ - '0');
	if (**str == '.')
	{
		fraction = 0.0;
		divisor = 1.0;
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			divisor *= 10.0;
			fraction = fraction * 10.0 + (*(*str)++ - '0');
		}
		result += fraction / divisor;
	}
	return (result * sign);
}

/*
** parse_vector3 - Parse "x,y,z" coordinates
*/
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
	return (point(x, y, z));
}

/*
** normalize_color_value - Clamp and normalize RGB value
*/
static double	normalize_color_value(int val)
{
	if (val < 0)
		return (0.0);
	if (val > 255)
		return (1.0);
	return (val / 255.0);
}

/*
** parse_color_rgb - Parse "R,G,B" and convert to [0,1]
*/
t_tuple	parse_color_rgb(char **str)
{
	int	r;
	int	g;
	int	b;

	r = (int)parse_double(str);
	if (**str == ',')
		(*str)++;
	g = (int)parse_double(str);
	if (**str == ',')
		(*str)++;
	b = (int)parse_double(str);
	return (color_d(normalize_color_value(r),
			normalize_color_value(g),
			normalize_color_value(b)));
}

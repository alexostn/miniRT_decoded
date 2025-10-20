/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:21:56 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 23:12:18 by oostapen         ###   ########.fr       */
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
** is_valid_number_end - Check if current character is valid after a number
** Valid endings: whitespace, comma, newline, null terminator
*/
static bool	is_valid_number_end(char c)
{
	return (c == ' ' || c == '\t' || c == ',' || c == '\n' 
		|| c == '\r' || c == '\0');
}

/*
** parse_double - Parse next floating point number with format validation
** Returns: parsed value
** On error: returns 0 and sets **str to invalid position for error detection
*/
double	parse_double(char **str)
{
	double	result;
	int		sign;
	double	fraction;
	double	divisor;

	skip_whitespace(str);
	sign = 1;
	if (**str == '-' || **str == '+')
	{
		sign = (**str == '-') ? -1 : 1;
		(*str)++;
	}
	result = 0.0;
	if (!(**str >= '0' && **str <= '9'))
		return (0.0);
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
	if (!is_valid_number_end(**str))
		return (0.0);
	return (result * sign);
}

/*
** parse_vector3 - Parse "x,y,z" coordinates with validation
** Returns: point/vector on success, tuple with w=-1.0 on error
*/
t_tuple	parse_vector3(char **str)
{
	double	x;
	double	y;
	double	z;
	t_tuple	error;

	error = (t_tuple){0, 0, 0, -1.0};
	x = parse_double(str);
	if (**str != ',')
		return (error);
	(*str)++;
	y = parse_double(str);
	if (**str != ',')
		return (error);
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
** Returns: color on success, tuple with w=-1.0 on error
*/
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

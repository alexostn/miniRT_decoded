/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:21:56 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 18:42:50 by oostapen         ###   ########.fr       */
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
static double	parse_fraction(char **str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			divisor *= 10.0;
			fraction = fraction * 10.0 + (*(*str)++ - '0');
		}
	}
	return (fraction / divisor);
}

bool	parse_double(char **str, double *val)
{
	double	result;
	int		sign;

	skip_whitespace(str);
	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	result = 0.0;
	if (!(**str >= '0' && **str <= '9'))
		return (false);
	while (**str >= '0' && **str <= '9')
		result = result * 10.0 + (*(*str)++ - '0');
	result += parse_fraction(str);
	if (!is_valid_number_end(**str))
		return (false);
	*val = result * sign;
	return (true);
}

/*
** parse_vector3 - Parse "x,y,z" coordinates with validation
** Returns: true on success, false on error
*/
bool	parse_vector3(char **str, t_tuple *vec)
{
	double	x;
	double	y;
	double	z;

	if (!parse_double(str, &x))
		return (false);
	if (**str != ',')
		return (false);
	(*str)++;
	if (!parse_double(str, &y))
		return (false);
	if (**str != ',')
		return (false);
	(*str)++;
	if (!parse_double(str, &z))
		return (false);
	*vec = point(x, y, z);
	return (true);
}

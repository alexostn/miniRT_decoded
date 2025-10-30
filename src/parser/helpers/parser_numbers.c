/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:10:21 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/26 21:10:39 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_numbers.h"
#include "tuples.h"

static void	skip_whitespace(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

static bool	is_valid_number_end(char c)
{
	return (c == ' ' || c == '\t' || c == ',' || c == '\n'
		|| c == '\r' || c == '\0');
}

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

bool	parse_vector3(char **str, t_tuple *vec)
{
	double	coords[3];
	int		index;

	index = 0;
	while (index < 3)
	{
		if (!parse_double(str, &coords[index]))
			return (false);
		if (index < 2)
		{
			if (**str != ',')
				return (false);
			(*str)++;
		}
		index++;
	}
	*vec = point(coords[0], coords[1], coords[2]);
	return (true);
}

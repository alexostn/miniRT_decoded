/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 21:37:33 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "colors.h"

bool	parse_double(char **str, double *val)
{
	char	*endptr;
	double	result;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	if (**str == '\0')
		return (false);
	result = ft_strtod(*str, &endptr);
	if (endptr == *str)
		return (false);
	*str = endptr;
	*val = result;
	return (true);
}

bool	parse_vector3(char **str, t_tuple *vec)
{
	double	x;
	double	y;
	double	z;

	while (**str == ' ' || **str == '\t')
		(*str)++;
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
	*vec = vector(x, y, z);
	return (true);
}

bool	parse_color_rgb(char **str, t_tuple *color)
{
	double	r;
	double	g;
	double	b;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	if (!parse_double(str, &r))
		return (false);
	if (**str != ',')
		return (false);
	(*str)++;
	if (!parse_double(str, &g))
		return (false);
	if (**str != ',')
		return (false);
	(*str)++;
	if (!parse_double(str, &b))
		return (false);
	if (!validate_range(r, 0, 255) || !validate_range(g, 0, 255)
		|| !validate_range(b, 0, 255))
		return (false);
	*color = color_d(r / 255.0, g / 255.0, b / 255.0);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:30:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 19:20:42 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	parse_color_rgb(char **str, t_tuple *color_out)
{
	double	r;
	double	g;
	double	b;

	if (!parse_double(str, &r) || !validate_range(r, 0, 255))
		return (false);
	if (**str != ',')
		return (false);
	(*str)++;
	if (!parse_double(str, &g) || !validate_range(g, 0, 255))
		return (false);
	if (**str != ',')
		return (false);
	(*str)++;
	if (!parse_double(str, &b) || !validate_range(b, 0, 255))
		return (false);
	*color_out = color_d(r / 255.0, g / 255.0, b / 255.0);
	return (true);
}

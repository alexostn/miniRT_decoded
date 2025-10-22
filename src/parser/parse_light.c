/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:52:35 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 19:14:35 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lights.h"
#include "libft.h"

/*
** check_end_of_line - Verify no extra arguments
*/
static bool	check_end_of_line(char *ptr)
{
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	return (*ptr == '\0' || *ptr == '\n' || *ptr == '\r');
}

static bool	parse_light_params(char *ptr, t_tuple *position,
				double *brightness, t_tuple *color)
{
	if (!parse_vector3(&ptr, position))
		return (false);
	if (!parse_double(&ptr, brightness) || !validate_range(*brightness, 0.0, 1.0))
		return (false);
	if (!parse_color_rgb(&ptr, color))
		return (false);
	return (check_end_of_line(ptr));
}

bool	parse_light(char *line, t_scene *scene)
{
	char			*ptr;
	t_tuple			position;
	double			brightness;
	t_tuple			color;

	ptr = line + 1;
	if (!parse_light_params(ptr, &position, &brightness, &color))
		return (false);
	scene->world.light = point_light(position,
			multiply_tuple_scalar(color, brightness));
	scene->world.light_present = true;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:52:35 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 23:10:06 by oostapen         ###   ########.fr       */
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

/*
** L -10,10,-10 0.7 255,255,255
**   ^          ^   ^
**   |          |   +-- RGB color (0-255)
**   |          +------ Brightness ratio (0-1)
**   +----------------- Position (x,y,z)
*/
bool	parse_light(char *line, t_scene *scene)
{
	char			*ptr;
	t_tuple			position;
	double			brightness;
	t_tuple			color;
	t_point_light	light;

	ptr = line + 1;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	position = parse_vector3(&ptr);
	if (position.w == -1.0)
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	brightness = parse_double(&ptr);
	if (!validate_range(brightness, 0.0, 1.0))
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	color = parse_color_rgb(&ptr);
	if (color.w == -1.0)
		return (false);
	if (!check_end_of_line(ptr))
		return (false);
	light = point_light(position, multiply_tuple_scalar(color, brightness));
	scene->world.light = light;
	return (true);
}

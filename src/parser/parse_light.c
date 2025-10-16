/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:52:35 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 23:02:42 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lights.h"
#include "libft.h"

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

	ptr = line;
	ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	position = parse_vector3(&ptr);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	brightness = parse_double(&ptr);
	if (!validate_range(brightness, 0.0, 1.0))
	{
		ft_putstr_fd("Error\nLight brightness must be in range [0.0, 1.0]\n",
			2);
		return (false);
	}
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	color = parse_color_rgb(&ptr);
	light = point_light(position, multiply_tuple_scalar(color, brightness));
	scene->world.light = light;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:05:51 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 03:03:35 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
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
** A 0.2 255,255,255
**   ^   ^   ^
**   |   |   +-- RGB color (0-255 each)
**   |   +------ ambient ratio (0.0-1.0)
**   +---------- identifier
*/
bool	parse_ambient(char *line, t_scene *scene, t_parse_state *state)
{
	char	*ptr;
	double	ratio;
	t_tuple	color;

	ptr = line + 1;
	if (!parse_double(&ptr, &ratio))
		parser_error_cleanup(state, "Ambient: Invalid ratio value");
	if (!validate_range(ratio, 0.0, 1.0))
		parser_error_cleanup(state, "Ambient: Ratio in range [0.0,1.0]");
	if (!parse_color_rgb(&ptr, &color))
		parser_error_cleanup(state, "Ambient: Invalid color RGB values");
	if (!check_end_of_line(ptr))
		parser_error_cleanup(state, "Ambient: Unexpected extra parameters");
	scene->world.ambient_ratio = ratio;
	scene->world.ambient_color = color;
	return (true);
}

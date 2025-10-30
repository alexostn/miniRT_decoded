/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_mandatory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:52:35 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/29 19:12:43 by oostapen         ###   ########.fr       */
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

static void	validate_light_brightness(double brightness, t_parse_state *state)
{
	if (!validate_range(brightness, 0.0, 1.0))
		parser_error_cleanup(state, "Light: Brightness in range [0.0,1.0]");
}

static void	parse_light_params(char *ptr, t_tuple *pos,
				t_tuple *color, t_parse_state *state)
{
	double	brightness;

	if (!parse_vector3(&ptr, pos))
		parser_error_cleanup(state, "Light: Invalid position coordinates");
	if (!parse_double(&ptr, &brightness))
		parser_error_cleanup(state, "Light: Invalid brightness value");
	validate_light_brightness(brightness, state);
	if (!parse_color_rgb(&ptr, color))
		parser_error_cleanup(state, "Light: Invalid color RGB values");
	if (!check_end_of_line(ptr))
		parser_error_cleanup(state, "Light: Unexpected extra parameters");
	*color = multiply_tuple_scalar(*color, brightness);
}

bool	parse_light(char *line, t_scene *scene, t_parse_state *state)
{
	char			*ptr;
	t_tuple			position;
	t_tuple			color;
	t_point_light	light;

	ptr = line + 1;
	parse_light_params(ptr, &position, &color, state);
	light = point_light(position, color);
	scene->world.light = light;
	scene->world.light_present = true;
	if (!world_add_light(&scene->world, light))
		parser_error_cleanup(state, "Light: Failed to add light");
	return (true);
}

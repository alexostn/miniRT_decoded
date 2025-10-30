/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cone_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 03:12:00 by alex              #+#    #+#             */
/*   Updated: 2025/10/27 03:12:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_cone.h"
#include "parser_utils.h"

static void	skip_ws(char **cursor)
{
	while (**cursor == ' ' || **cursor == '\t')
		(*cursor)++;
}

static void	parse_center_axis(char **cursor, t_cone_input *input,
				t_parse_state *state)
{
	double	mag;

	(*cursor) += 2;
	skip_ws(cursor);
	if (!parse_vector3(cursor, &input->center))
		parser_error_cleanup(state, "Cone: Invalid center coordinates");
	skip_ws(cursor);
	if (!parse_vector3(cursor, &input->axis))
		parser_error_cleanup(state, "Cone: Invalid axis vector");
	input->axis.w = 0.0;
	mag = magnitude_of_vector(input->axis);
	if (mag < 0.999 || mag > 1.001)
		parser_error("Cone: Axis must be normalized (x²+y²+z²=1)",
			state->line_num);
}

static void	parse_dimensions(char **cursor, t_cone_input *input,
				t_parse_state *state)
{
	skip_ws(cursor);
	if (!parse_double(cursor, &input->diameter))
		parser_error_cleanup(state, "Cone: Invalid diameter value");
	if (input->diameter <= 0.0)
		parser_error_cleanup(state, "Cone: Diameter must be positive");
	skip_ws(cursor);
	if (!parse_double(cursor, &input->height))
		parser_error_cleanup(state, "Cone: Invalid height value");
	if (input->height <= 0.0)
		parser_error_cleanup(state, "Cone: Height must be positive");
}

static void	parse_color(char **cursor, t_cone_input *input,
				t_parse_state *state)
{
	skip_ws(cursor);
	if (!parse_color_rgb(cursor, &input->color))
		parser_error_cleanup(state, "Cone: Invalid color RGB values");
}

t_cone_input	cone_parse_input(char *line, t_parse_state *state)
{
	t_cone_input	input;
	char			*cursor;

	cursor = line;
	parse_center_axis(&cursor, &input, state);
	parse_dimensions(&cursor, &input, state);
	parse_color(&cursor, &input, state);
	return (input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 04:35:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/29 19:10:08 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_cone.h"

bool	parse_cone(char *line, t_scene *scene, t_parse_state *state)
{
	t_cone_input	input;
	t_cone			cone;
	t_matrix		transform;

	input = cone_parse_input(line, state);
	cone = cone_create();
	if (!cone_build_transform(input, &transform))
		parser_error("Cone: Cannot create orientation matrix",
			state->line_num);
	cone.shape.transform = transform;
	cone_apply_properties(&cone, input);
	if (!world_add_cone(&scene->world, cone))
		parser_error("Cone: Too many cones (MAX_OBJECTS reached)",
			state->line_num);
	return (true);
}

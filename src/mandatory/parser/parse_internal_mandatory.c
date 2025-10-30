/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal_mandatory.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:18:06 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/29 19:11:30 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	init_parse_state(t_scene *scene, t_parse_state *state)
{
	scene->world = world_make();
	state->has_ambient = false;
	state->has_camera = false;
	state->has_light = false;
	state->line_num = 0;
}

static bool	dispatch_ace(const char *line, t_scene *scene,
				t_parse_state *state)
{
	if (ft_strncmp(line, "A ", 2) == 0)
	{
		if (state->has_ambient)
			parser_error_cleanup(state,
				"Ambient light (A) can only be defined once");
		state->has_ambient = true;
		return (parse_ambient((char *)line, scene, state));
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (state->has_camera)
			parser_error_cleanup(state,
				"Camera (C) can only be defined once");
		state->has_camera = true;
		return (parse_camera((char *)line, scene, state));
	}
	return (false);
}

/* Check for common case-sensitivity errors */
static void	check_case_errors(const char *line, t_parse_state *state)
{
	if (ft_strncmp(line, "a ", 2) == 0)
		parser_error_cleanup(state,
			"Invalid identifier 'a' (use 'A' for ambient light)");
	if (ft_strncmp(line, "c ", 2) == 0)
		parser_error_cleanup(state,
			"Invalid identifier 'c' (use 'C' for camera)");
	if (ft_strncmp(line, "l ", 2) == 0)
		parser_error_cleanup(state,
			"Invalid identifier 'l' (use 'L' for light)");
}

bool	dispatch_element(const char *line, t_scene *scene,
			t_parse_state *state)
{
	if (line[0] == '#' || line[0] == '\0')
		return (true);
	if (dispatch_ace(line, scene, state))
		return (true);
	if (ft_strncmp(line, "L ", 2) == 0)
	{
		if (state->has_light)
			parser_error_cleanup(state,
				"Only ONE light allowed in mandatory part");
		state->has_light = true;
		return (parse_light((char *)line, scene, state));
	}
	if (ft_strncmp(line, "sp ", 3) == 0)
		return (parse_sphere((char *)line, scene, state));
	if (ft_strncmp(line, "pl ", 3) == 0)
		return (parse_plane((char *)line, scene, state));
	if (ft_strncmp(line, "cy ", 3) == 0)
		return (parse_cylinder((char *)line, scene, state));
	if (ft_strncmp(line, "co ", 3) == 0)
		parser_error_cleanup(state,
			"Cones (co) are only available in BONUS part");
	check_case_errors(line, state);
	return (false);
}

void	validate_scene(t_parse_state *state)
{
	if (!state->has_ambient)
		parser_error("Scene validation failed: Missing ambient light (A)", 0);
	if (!state->has_camera)
		parser_error("Scene validation failed: Missing camera (C)", 0);
	if (!state->has_light)
		parser_error("Scene validation failed: Missing light (L)", 0);
}

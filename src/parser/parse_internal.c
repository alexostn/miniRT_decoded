/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:18:06 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 03:06:34 by oostapen         ###   ########.fr       */
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
			parser_error("Ambient light (A) can only be defined once",
				state->line_num);
		state->has_ambient = true;
		return (parse_ambient((char *)line, scene, state));
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (state->has_camera)
			parser_error("Camera (C) can only be defined once",
				state->line_num);
		state->has_camera = true;
		return (parse_camera((char *)line, scene, state));
	}
	return (false);
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
			parser_error("Light can only be defined once in mandatory",
				state->line_num);
		state->has_light = true;
		return (parse_light((char *)line, scene, state));
	}
	if (ft_strncmp(line, "sp ", 3) == 0)
		return (parse_sphere((char *)line, scene, state));
	if (ft_strncmp(line, "pl ", 3) == 0)
		return (parse_plane((char *)line, scene, state));
	if (ft_strncmp(line, "cy ", 3) == 0)
		return (parse_cylinder((char *)line, scene, state));
	return (false);
}

void	validate_scene(t_parse_state *state)
{
	if (!state->has_ambient)
		parser_error("Scene validation failed: Missing ambient light (A)", 0);
	if (!state->has_camera)
		parser_error("Scene validation failed: Missing camera (C)", 0);
	if (!state->has_light)
		parser_error("Scene validation failed: Missing at least one light (L)",
			0);
}

void	parser_error(const char *msg, int line_num)
{
	char	*line_str;

	ft_putstr_fd("Error\n", 2);
	if (line_num > 0)
	{
		ft_putstr_fd("Line ", 2);
		line_str = ft_itoa(line_num);
		if (line_str)
		{
			ft_putstr_fd(line_str, 2);
			ft_putstr_fd(": ", 2);
			free(line_str);
		}
	}
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

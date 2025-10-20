/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:18:06 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 18:05:36 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

void	init_parse_state(t_scene *scene, t_parse_state *state)
{
	scene->world = world_make();
	state->has_ambient = false;
	state->has_camera = false;
	state->has_light = false;
	state->line_num = 0;
}

bool	dispatch_element(const char *line, t_scene *scene,
			t_parse_state *state)
{
	printf("DEBUG: dispatch_element called with line %d: '%s'\n", state->line_num, line);
	if (line[0] == '#' || line[0] == '\0')
		return (true);
	if (ft_strncmp(line, "A ", 2) == 0)
	{
		if (state->has_ambient)
			parser_error("Ambient light (A) can only be defined once",
				state->line_num);
		state->has_ambient = true;
		return (parse_ambient((char *)line, scene));
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (state->has_camera)
			parser_error("Camera (C) can only be defined once", state->line_num);
		state->has_camera = true;
		return (parse_camera((char *)line, scene));
	}
	if (ft_strncmp(line, "L ", 2) == 0)
	{
		state->has_light = true;
		return (parse_light((char *)line, scene));
	}
	if (ft_strncmp(line, "sp ", 3) == 0)
	{
		printf("DEBUG: Dispatching to parse_sphere\n");
		return (parse_sphere((char *)line, scene));
	}
	printf("DEBUG: No match found for identifier\n");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:18:06 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/17 00:10:16 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/* ========================================================================== */
/* START: Initialize parser state                                            */
/* ========================================================================== */

/*
** init_parse_state - Initialize parser state and scene
** @scene: Pointer to scene structure
** @state: Pointer to parser state structure
**
** Initializes empty world and resets all state flags to false.
*/
void	init_parse_state(t_scene *scene, t_parse_state *state)
{
	scene->world = world_make();
	state->has_ambient = false;
	state->has_camera = false;
	state->has_light = false;
	state->line_num = 0;
}

/* ========================================================================== */
/* END: Initialize parser state                                              */
/* ========================================================================== */

/* ========================================================================== */
/* START: Dispatch element to correct parser                                 */
/* ========================================================================== */

/*
** dispatch_element - Route line to appropriate element parser
** @line: Trimmed line from .rt file
** @scene: Scene being populated
** @state: Parser state tracker
**
** Returns: true on success, false on parse error
**
** Recognizes:
** - A   : Ambient light
** - C   : Camera
** - L   : Light
** - sp  : Sphere
** - #   : Comment (ignored)
*/
bool	dispatch_element(const char *line, t_scene *scene,
			t_parse_state *state)
{
	if (line[0] == '#')
		return (true);
	if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
	{
		state->has_ambient = true;
		return (parse_ambient((char *)line, scene));
	}
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		state->has_camera = true;
		return (parse_camera((char *)line, scene));
	}
	if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
	{
		state->has_light = true;
		return (parse_light((char *)line, scene));
	}
	if (line[0] == 's' && line[1] == 'p' && (line[2] == ' ' || line[2] == '\t'))
		return (parse_sphere((char *)line, scene));
	parser_error("Invalid scene file", state->line_num);
	return (false);
}

/*
** validate_scene - Check required elements are present
** @state: Parser state with tracking flags
**
** Exits with error if any required element is missing:
** - Ambient light (A)
** - Camera (C)
** - Light (L)
*/
void	validate_scene(t_parse_state *state)
{
	if (!state->has_ambient)
		parser_error("Missing ambient light (A)", 0);
	if (!state->has_camera)
		parser_error("Missing camera (C)", 0);
	if (!state->has_light)
		parser_error("Missing light (L)", 0);
}

/*
** parser_error - Print error message and exit
** @msg: Error message to display
** @line_num: Line number where error occurred (0 for general errors)
**
** Prints "Error\n[Line X: ]<message>" and exits with status 1.
*/
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

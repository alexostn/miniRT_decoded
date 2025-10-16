/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:15:27 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/17 00:33:51 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include "get_next_line.h"
#include "libft.h"

static bool	parse_single_line(char *line, t_scene *sc, t_parse_state *st)
{
	char	*trimmed;
	bool	result;

	printf("DEBUG parse_single_line: raw='%s'\n", line);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
	{
		printf("DEBUG: ft_strtrim failed!\n");
		return (false);
	}
	printf("DEBUG: trimmed='%s'\n", trimmed);
	if (!*trimmed)
	{
		printf("DEBUG: Empty line, skipping\n");
		free(trimmed);
		return (true);
	}
	printf("DEBUG: Calling dispatch_element\n");
	result = dispatch_element(trimmed, sc, st);
	printf("DEBUG: dispatch returned %d\n", result);
	free(trimmed);
	return (result);
}


/*
line = get_next_line_bonus(fd);  // ⚠️ HEAP - malloc and free(line);
*/
static bool	read_scene_file(int fd, t_scene *sc, t_parse_state *st)
{
	char	*line;
	
	while (1)
	{
		line = get_next_line_bonus(fd);
		if (!line)
		break ;
		st->line_num++;
		if (!parse_single_line(line, sc, st))
		{
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}

/*
** parse_scene_file - Main parser entry point
** @filename: Path to .rt scene file
** Returns: Populated scene structure
** On error: Prints "Error\n<message>" and exits
*/
t_scene	parse_scene_file(const char *filename)
{
	int				fd;
	t_scene			scene;
	t_parse_state	state;
	
	init_parse_state(&scene, &state);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	parser_error("Failed to open file", 0);
	if (!read_scene_file(fd, &scene, &state))
	{
		close(fd);
		parser_error("Invalid scene file", state.line_num);
	}
	close(fd);
	validate_scene(&state);
	return (scene);
}

/*
RENAMED from process_line to avoid conflict with GNL's process_line

bool parse_single_line(char *line, t_scene *sc, t_parse_state *st)
{
	// 1. Trim whitespace (ft_strtrim)
	// 2. Check for empty string
	// 3. Parse element (dispatch_element)
	// 4. Return true/false (success/error)
	
	// Example:
	// line = "  sp 0,0,0 2.0 255,0,0  \n"
	// -> trim -> "sp 0,0,0 2.0 255,0,0"
	// -> dispatch -> parse_sphere()
	// -> return true
}
*/
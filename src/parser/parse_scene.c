/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:15:27 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/17 00:50:16 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"
#include "libft.h"

static bool	parse_single_line(char *line, t_scene *sc, t_parse_state *st)
{
	bool	result;

	st->current_trimmed = ft_strtrim(line, " \t\n\r\v\f");
	if (!st->current_trimmed)
		parser_error_cleanup(st, "Memory allocation failed during trim");
	result = dispatch_element(st->current_trimmed, sc, st);
	free(st->current_trimmed);
	st->current_trimmed = NULL;
	if (!result)
		parser_error_cleanup(st, "Invalid identifier or scene format");
	return (result);
}

static void	read_scene_file(int fd, t_scene *sc, t_parse_state *st)
{
	st->current_line = get_next_line_bonus(fd);
	while (st->current_line)
	{
		st->line_num++;
		parse_single_line(st->current_line, sc, st);
		free(st->current_line);
		st->current_line = NULL;
		st->current_line = get_next_line_bonus(fd);
	}
}

t_scene	parse_scene_file(const char *filename)
{
	t_scene			scene;
	t_parse_state	state;

	init_parse_state(&scene, &state);
	state.fd = open(filename, O_RDONLY);
	state.current_line = NULL;
	state.current_trimmed = NULL;
	if (state.fd < 0)
		parser_error("Failed to open scene file", 0);
	read_scene_file(state.fd, &scene, &state);
	close(state.fd);
	state.fd = -1;
	validate_scene(&state);
	return (scene);
}

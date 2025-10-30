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
	char	*trimmed;
	bool	result;

	trimmed = ft_strtrim(line, " \t\n\r\v\f");
	if (!trimmed)
		parser_error("Memory allocation failed during trim", st->line_num);
	result = dispatch_element(trimmed, sc, st);
	free(trimmed);
	if (!result)
		parser_error("Invalid identifier or scene format", st->line_num);
	return (result);
}

static void	read_scene_file(int fd, t_scene *sc, t_parse_state *st)
{
	char	*line;

	line = get_next_line_bonus(fd);
	while (line)
	{
		st->line_num++;
		parse_single_line(line, sc, st);
		free(line);
		line = get_next_line_bonus(fd);
	}
}

t_scene	parse_scene_file(const char *filename)
{
	int				fd;
	t_scene			scene;
	t_parse_state	state;

	init_parse_state(&scene, &state);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parser_error("Failed to open scene file", 0);
	read_scene_file(fd, &scene, &state);
	close(fd);
	validate_scene(&state);
	return (scene);
}

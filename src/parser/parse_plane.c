/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 03:10:27 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "planes.h"
#include "libft.h"

static void	skip_ws(char **ptr)
{
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
}

static void	parse_pl_vectors(char **ptr, t_tuple *point,
				t_tuple *normal, t_parse_state *state)
{
	double	mag;

	*ptr += 2;
	skip_ws(ptr);
	if (!parse_vector3(ptr, point))
		parser_error("Plane: Invalid point coordinates", state->line_num);
	skip_ws(ptr);
	if (!parse_vector3(ptr, normal))
		parser_error("Plane: Invalid normal vector", state->line_num);
	mag = magnitude_of_vector(*normal);
	if (mag < 0.999 || mag > 1.001)
		parser_error("Plane: Normal must be normalized (len=1)",
			state->line_num);
}

static t_plane	create_plane_with_transform(t_tuple point)
{
	t_plane	plane;

	plane = plane_create();
	plane = plane_set_transform(plane, translation(point.x, point.y,
				point.z));
	return (plane);
}

bool	parse_plane(char *line, t_scene *scene, t_parse_state *state)
{
	t_tuple	point;
	t_tuple	normal;
	t_tuple	color;
	t_plane	plane;

	parse_pl_vectors(&line, &point, &normal, state);
	skip_ws(&line);
	if (!parse_color_rgb(&line, &color))
		parser_error("Plane: Invalid color RGB values", state->line_num);
	plane = create_plane_with_transform(point);
	plane.shape.material.color = color;
	world_add_plane(&scene->world, plane);
	return (true);
}

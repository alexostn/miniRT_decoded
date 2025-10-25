/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 03:51:38 by oostapen         ###   ########.fr       */
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
	normal->w = 0.0;
	mag = magnitude_of_vector(*normal);
	if (mag < 0.999 || mag > 1.001)
		parser_error("Plane: Normal must be normalized (x²+y²+z²=1)",
			state->line_num);
}

static t_plane	create_plane_with_transform(t_tuple point, t_tuple normal,
		t_parse_state *state)
{
	t_plane	plane;
	t_matrix	orientation;
	t_matrix	translate;
	t_matrix	transform;

	plane = plane_create();
	if (!build_orientation_matrix(normalize_vector(normal), &orientation))
		parser_error("Plane: Failed to apply normal rotation", state->line_num);
	translate = translation(point.x, point.y, point.z);
	transform = mat_mul(translate, orientation);
	plane = plane_set_transform(plane, transform);
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
	plane = create_plane_with_transform(point, normal, state);
	plane.shape.material.color = color;
	if (!world_add_plane(&scene->world, plane))
		parser_error("Plane: Too many planes (MAX_OBJECTS reached)",
			state->line_num);
	return (true);
}

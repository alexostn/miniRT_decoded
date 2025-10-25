/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 03:51:38 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cylinders.h"
#include "libft.h"

static void	skip_ws(char **ptr)
{
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
}

static void	parse_cy_vectors(char **ptr, t_tuple *center,
				t_tuple *axis, t_parse_state *state)
{
	double	mag;

	*ptr += 2;
	skip_ws(ptr);
	if (!parse_vector3(ptr, center))
		parser_error("Cylinder: Invalid center coordinates", state->line_num);
	skip_ws(ptr);
	if (!parse_vector3(ptr, axis))
		parser_error("Cylinder: Invalid axis vector", state->line_num);
	mag = magnitude_of_vector(*axis);
	if (mag < 0.999 || mag > 1.001)
		parser_error("Cylinder: Axis must be normalized (x²+y²+z²=1)",
			state->line_num);
}

static void	parse_cy_dimensions(char **ptr, double *diam,
				double *height, t_parse_state *state)
{
	skip_ws(ptr);
	if (!parse_double(ptr, diam))
		parser_error("Cylinder: Invalid diameter value", state->line_num);
	if (*diam <= 0)
		parser_error("Cylinder: Diameter must be positive", state->line_num);
	skip_ws(ptr);
	if (!parse_double(ptr, height))
		parser_error("Cylinder: Invalid height value", state->line_num);
	if (*height <= 0)
		parser_error("Cylinder: Height must be positive", state->line_num);
}

static t_matrix	create_cy_transform(t_tuple center, double diam, double h)
{
	t_matrix	scale;
	t_matrix	trans;

	scale = scaling(diam / 2.0, h, diam / 2.0);
	trans = translation(center.x, center.y, center.z);
	return (mat_mul(trans, scale));
}

bool	parse_cylinder(char *line, t_scene *scene, t_parse_state *state)
{
	t_tuple		center;
	t_tuple		axis;
	double		dims[2];
	t_tuple		color;
	t_cylinder	cy;

	parse_cy_vectors(&line, &center, &axis, state);
	parse_cy_dimensions(&line, &dims[0], &dims[1], state);
	skip_ws(&line);
	if (!parse_color_rgb(&line, &color))
		parser_error("Cylinder: Invalid color RGB values", state->line_num);
	cy = cylinder_create();
	cy = cylinder_set_transform(cy, create_cy_transform(center, dims[0],
				dims[1]));
	cy.shape.material.color = color;
	world_add_cylinder(&scene->world, cy);
	return (true);
}

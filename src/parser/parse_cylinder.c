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

static void	parse_cy_vectors(char **ptr, t_tuple *center,
				t_tuple *axis, t_parse_state *state);
static void	parse_cy_dimensions(char **ptr, double *diam,
				double *height, t_parse_state *state);
static bool	create_cy_transform(t_tuple center, t_tuple axis,
				double diameter, t_matrix *out);
static void	apply_cy_properties(t_cylinder *cy, t_tuple color, double height);

bool	parse_cylinder(char *line, t_scene *scene, t_parse_state *state)
{
	t_tuple		center;
	t_tuple		axis;
	double		dims[2];
	t_tuple		color;
	t_cylinder	cy;

	parse_cy_vectors(&line, &center, &axis, state);
	parse_cy_dimensions(&line, &dims[0], &dims[1], state);
	while (*line == ' ' || *line == '\t')
		line++;
	if (!parse_color_rgb(&line, &color))
		parser_error("Cylinder: Invalid color RGB values", state->line_num);
	cy = cylinder_create();
	if (!create_cy_transform(center, axis, dims[0], &cy.shape.transform))
		parser_error("Cylinder: Failed to apply axis rotation",
			state->line_num);
	apply_cy_properties(&cy, color, dims[1]);
	if (!world_add_cylinder(&scene->world, cy))
		parser_error("Cylinder: Too many cylinders (MAX_OBJECTS reached)",
			state->line_num);
	return (true);
}

static void	parse_cy_vectors(char **ptr, t_tuple *center,
				t_tuple *axis, t_parse_state *state)
{
	double	mag;

	*ptr += 2;
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	if (!parse_vector3(ptr, center))
		parser_error("Cylinder: Invalid center coordinates", state->line_num);
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	if (!parse_vector3(ptr, axis))
		parser_error("Cylinder: Invalid axis vector", state->line_num);
	axis->w = 0.0;
	mag = magnitude_of_vector(*axis);
	if (mag < 0.999 || mag > 1.001)
		parser_error("Cylinder: Axis must be normalized (x²+y²+z²=1)",
			state->line_num);
}

static void	parse_cy_dimensions(char **ptr, double *diam,
				double *height, t_parse_state *state)
{
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	if (!parse_double(ptr, diam))
		parser_error("Cylinder: Invalid diameter value", state->line_num);
	if (*diam <= 0)
		parser_error("Cylinder: Diameter must be positive", state->line_num);
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	if (!parse_double(ptr, height))
		parser_error("Cylinder: Invalid height value", state->line_num);
	if (*height <= 0)
		parser_error("Cylinder: Height must be positive", state->line_num);
}

static bool	create_cy_transform(t_tuple center, t_tuple axis,
				double diameter, t_matrix *out)
{
	t_matrix	scale;
	t_matrix	trans;
	t_matrix	orientation;

	if (!build_orientation_matrix(normalize_vector(axis), &orientation))
		return (false);
	scale = scaling(diameter / 2.0, 1.0, diameter / 2.0);
	trans = translation(center.x, center.y, center.z);
	*out = mat_mul(trans, mat_mul(orientation, scale));
	return (true);
}

static void	apply_cy_properties(t_cylinder *cy, t_tuple color, double height)
{
	cy->minimum = -(height / 2.0);
	cy->maximum = height / 2.0;
	cy->closed = true;
	cy->shape.material.color = color;
}

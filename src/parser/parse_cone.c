/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 04:35:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:32:46 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cones.h"
#include "libft.h"

static void	skip_ws(char **ptr)
{
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
}

static void	parse_co_vectors(char **ptr, t_tuple *center,
				t_tuple *axis, t_parse_state *state)
{
	double	mag;

	*ptr += 2;
	skip_ws(ptr);
	if (!parse_vector3(ptr, center))
		parser_error("Cone: Invalid center coordinates", state->line_num);
	skip_ws(ptr);
	if (!parse_vector3(ptr, axis))
		parser_error("Cone: Invalid axis vector", state->line_num);
	mag = magnitude_of_vector(*axis);
	if (mag < 0.999 || mag > 1.001)
		parser_error("Cone: Axis must be normalized (x²+y²+z²=1)",
			state->line_num);
}

static void	parse_co_dimensions(char **ptr, double *diam,
				double *height, t_parse_state *state)
{
	skip_ws(ptr);
	if (!parse_double(ptr, diam))
		parser_error("Cone: Invalid diameter value", state->line_num);
	if (*diam <= 0)
		parser_error("Cone: Diameter must be positive", state->line_num);
	skip_ws(ptr);
	if (!parse_double(ptr, height))
		parser_error("Cone: Invalid height value", state->line_num);
	if (*height <= 0)
		parser_error("Cone: Height must be positive", state->line_num);
}

static t_matrix	create_co_transform(t_tuple center, double diam, double h)
{
	t_matrix	scale;
	t_matrix	trans;

	scale = scaling(diam / 2.0, h, diam / 2.0);
	trans = translation(center.x, center.y, center.z);
	return (mat_mul(trans, scale));
}

bool	parse_cone(char *line, t_scene *scene, t_parse_state *state)
{
	t_tuple	center;
	t_tuple	axis;
	double	dims[2];
	t_tuple	color;
	t_cone	co;

	parse_co_vectors(&line, &center, &axis, state);
	parse_co_dimensions(&line, &dims[0], &dims[1], state);
	skip_ws(&line);
	if (!parse_color_rgb(&line, &color))
		parser_error("Cone: Invalid color RGB values", state->line_num);
	co = cone_create();
	co.shape.transform = create_co_transform(center, dims[0], dims[1]);
	co.shape.material.color = color;
	world_add_cone(&scene->world, co);
	return (true);
}

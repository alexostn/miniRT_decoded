/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 04:35:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/27 02:25:04 by alex             ###   ########.fr       */
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

/*
** For double cone (two cones joined at apex):
**   co.minimum = -dims[1];
**   co.closed = false;
*/
bool	parse_cone(char *line, t_scene *scene, t_parse_state *state)
{
	t_tuple		data[3];
	double		dims[2];
	t_cone		co;
	t_matrix	orient;

	parse_co_vectors(&line, &data[0], &data[1], state);
	parse_co_dimensions(&line, &dims[0], &dims[1], state);
	skip_ws(&line);
	if (!parse_color_rgb(&line, &data[2]))
		parser_error("Cone: Invalid color RGB values", state->line_num);
	co = cone_create();
	if (!build_orientation_matrix(normalize_vector(data[1]), &orient))
		parser_error("Cone: Cannot create orientation matrix", state->line_num);
	co.shape.transform = mat_mul(translation(data[0].x, data[0].y, data[0].z),
			mat_mul(orient, scaling(dims[0] / 2.0, 1.0, dims[0] / 2.0)));
	co.minimum = 0.0;
	co.maximum = dims[1];
	co.closed = true;
	co.shape.material.color = data[2];
	world_add_cone(&scene->world, co);
	return (true);
}

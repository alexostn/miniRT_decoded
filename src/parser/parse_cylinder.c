/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 22:13:19 by oostapen         ###   ########.fr       */
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

static bool	parse_cy_vectors(char **ptr, t_tuple *center, t_tuple *axis)
{
	*ptr += 2;
	skip_ws(ptr);
	if (!parse_vector3(ptr, center))
		return (false);
	skip_ws(ptr);
	if (!parse_vector3(ptr, axis))
		return (false);
	if (!validate_normalized(*axis))
		return (false);
	return (true);
}

static bool	parse_cy_dimensions(char **ptr, double *diam, double *height)
{
	skip_ws(ptr);
	if (!parse_double(ptr, diam))
		return (false);
	skip_ws(ptr);
	if (!parse_double(ptr, height))
		return (false);
	return (true);
}

static t_matrix	create_cy_transform(t_tuple center, double diam, double h)
{
	t_matrix	scale;
	t_matrix	trans;

	scale = scaling(diam / 2.0, h, diam / 2.0);
	trans = translation(center.x, center.y, center.z);
	return (mat_mul(trans, scale));
}

bool	parse_cylinder(char *line, t_scene *scene)
{
	t_tuple		center;
	t_tuple		axis;
	double		dims[2];
	t_tuple		color;
	t_cylinder	cy;

	if (!parse_cy_vectors(&line, &center, &axis))
		return (false);
	if (!parse_cy_dimensions(&line, &dims[0], &dims[1]))
		return (false);
	skip_ws(&line);
	if (!parse_color_rgb(&line, &color))
		return (false);
	cy = cylinder_create();
	cy = cylinder_set_transform(cy, create_cy_transform(center, dims[0],
				dims[1]));
	cy.shape.material.color = color;
	world_add_cylinder(&scene->world, cy);
	return (true);
}

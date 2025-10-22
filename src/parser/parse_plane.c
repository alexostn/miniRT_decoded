/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 22:15:10 by oostapen         ###   ########.fr       */
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

static bool	parse_pl_vectors(char **ptr, t_tuple *point, t_tuple *normal)
{
	*ptr += 2;
	skip_ws(ptr);
	if (!parse_vector3(ptr, point))
		return (false);
	skip_ws(ptr);
	if (!parse_vector3(ptr, normal))
		return (false);
	if (!validate_normalized(*normal))
		return (false);
	return (true);
}

static t_plane	create_plane_with_transform(t_tuple point)
{
	t_plane	plane;

	plane = plane_create();
	plane = plane_set_transform(plane, translation(point.x, point.y,
				point.z));
	return (plane);
}

bool	parse_plane(char *line, t_scene *scene)
{
	t_tuple	point;
	t_tuple	normal;
	t_tuple	color;
	t_plane	plane;

	if (!parse_pl_vectors(&line, &point, &normal))
		return (false);
	skip_ws(&line);
	if (!parse_color_rgb(&line, &color))
		return (false);
	plane = create_plane_with_transform(point);
	plane.shape.material.color = color;
	world_add_plane(&scene->world, plane);
	return (true);
}

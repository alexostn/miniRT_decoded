/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 21:19:38 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "planes.h"
#include "libft.h"

bool	parse_plane(char *line, t_scene *scene)
{
	char		*ptr;
	t_tuple		point;
	t_tuple		normal;
	t_tuple		color;
	t_plane		plane;
	t_material	material;

	ptr = line + 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_vector3(&ptr, &point))
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_vector3(&ptr, &normal))
		return (false);
	if (!validate_normalized(normal))
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_color_rgb(&ptr, &color))
		return (false);
	plane = plane_create();
	plane = plane_set_transform(plane, translation(point.x, point.y, point.z));
	material = material_create();
	material.color = color;
	plane = plane_set_material(plane, material);
	world_add_plane(&scene->world, plane);
	return (true);
}

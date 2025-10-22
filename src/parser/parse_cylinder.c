/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 21:19:38 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cylinders.h"
#include "libft.h"

bool	parse_cylinder(char *line, t_scene *scene)
{
	char		*ptr;
	t_tuple		center;
	t_tuple		axis;
	double		diameter;
	double		height;
	t_tuple		color;
	t_cylinder	cylinder;
	t_material	material;
	t_matrix	transform;

	ptr = line + 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_vector3(&ptr, &center))
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_vector3(&ptr, &axis))
		return (false);
	if (!validate_normalized(axis))
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_double(&ptr, &diameter))
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_double(&ptr, &height))
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_color_rgb(&ptr, &color))
		return (false);
	cylinder = cylinder_create();
	transform = mat_mul(translation(center.x, center.y, center.z),
			scaling(diameter / 2.0, height, diameter / 2.0));
	cylinder = cylinder_set_transform(cylinder, transform);
	material = material_create();
	material.color = color;
	cylinder = cylinder_set_material(cylinder, material);
	world_add_cylinder(&scene->world, cylinder);
	return (true);
}

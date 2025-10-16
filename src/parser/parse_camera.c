/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:35:58 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 22:54:40 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** C 0,0,-5 0,0,1 70
**   ^      ^     ^
**   |      |     +-- FOV in degrees (0-180)
**   |      +-------- Orientation vector (normalized direction where camera looks)
**   +--------------- Position (x,y,z)
**
** NOTE: Orientation is a DIRECTION VECTOR, not a target point!
** We compute target point as: to = from + orientation
**
** Returns: true on success, false on parse error
*/
bool	parse_camera(char *line, t_scene *scene)
{
	char	*ptr;
	t_tuple	from;
	t_tuple	orientation;
	t_tuple	to;
	double	fov;

	ptr = line;
	ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	from = parse_vector3(&ptr);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	orientation = parse_vector3(&ptr);
	if (!validate_normalized(orientation))
	{
		ft_putstr_fd("Error\nCamera orientation must be normalized\n", 2);
		return (false);
	}
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	fov = parse_double(&ptr);
	if (!validate_range(fov, 0.0, 180.0))
	{
		ft_putstr_fd("Error\nCamera FOV must be in range [0, 180]\n", 2);
		return (false);
	}
	scene->camera = camera_make(800, 600, degrees_to_radians(fov));
	to = add(from, orientation);
	scene->camera.transform = view_transform(from, to, vector(0, 1, 0));
	return (true);
}

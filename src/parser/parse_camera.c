/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:35:58 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 18:59:31 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "camera.h"

/*
** C 0,0,-5 0,0,1 70
**   ^      ^     ^
**   |      |     +-- FOV in degrees (0-180)
**   |      +-------- Orientation vector(normalized where camera looks)
**   +--------------- Position (x,y,z)
**
** NOTE: Orientation is a DIRECTION VECTOR, not a target point!
** We compute target point as: to = from + orientation
**
** Returns: true on success, false on parse error
*/
/*
** check_end_of_line - Verify no extra arguments
*/
static bool	check_end_of_line(char *ptr)
{
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	return (*ptr == '\0' || *ptr == '\n' || *ptr == '\r');
}

static bool	parse_camera_params(char *ptr, t_tuple *from,
				t_tuple *orientation, double *fov)
{
	if (!parse_vector3(&ptr, from))
		return (false);
	if (!parse_vector3(&ptr, orientation) || !validate_normalized(*orientation))
		return (false);
	if (!parse_double(&ptr, fov) || !validate_range(*fov, 0, 180))
		return (false);
	return (check_end_of_line(ptr));
}

bool	parse_camera(char *line, t_scene *scene)
{
	char	*ptr;
	t_tuple	from;
	t_tuple	orientation;
	double	fov;

	ptr = line + 1;
	if (!parse_camera_params(ptr, &from, &orientation, &fov))
		return (false);
	scene->camera = camera_make(WIN_WIDTH, WIN_HEIGHT,
			fov * (M_PI / 180.0));
	scene->camera.transform = view_transform(from,
			add(from, orientation),
			vector(0, 1, 0));
	return (true);
}

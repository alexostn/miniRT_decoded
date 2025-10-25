/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:35:58 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 03:22:07 by oostapen         ###   ########.fr       */
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

static void	validate_camera_orientation(t_tuple orientation,
				t_parse_state *state)
{
	double	mag;

	mag = magnitude_of_vector(orientation);
	if (mag < 0.999 || mag > 1.001)
		parser_error("Camera: Orientation must be normalized (len=1)",
			state->line_num);
}

static void	parse_cam_params(char *ptr, t_tuple *from,
				t_tuple *orient, t_parse_state *state)
{
	double	fov;

	if (!parse_vector3(&ptr, from))
		parser_error("Camera: Invalid position coordinates", state->line_num);
	if (!parse_vector3(&ptr, orient))
		parser_error("Camera: Invalid orientation vector", state->line_num);
	validate_camera_orientation(*orient, state);
	if (!parse_double(&ptr, &fov))
		parser_error("Camera: Invalid FOV value", state->line_num);
	if (fov <= 0 || fov > 180)
		parser_error("Camera: FOV must be > 0 and <= 180 degrees",
			state->line_num);
	if (!check_end_of_line(ptr))
		parser_error("Camera: Unexpected extra parameters", state->line_num);
	from->w = fov;
}

bool	parse_camera(char *line, t_scene *scene, t_parse_state *state)
{
	char	*ptr;
	t_tuple	from;
	t_tuple	orientation;

	ptr = line + 1;
	parse_cam_params(ptr, &from, &orientation, state);
	scene->camera = camera_make(WIN_WIDTH, WIN_HEIGHT,
			from.w * (M_PI / 180.0));
	scene->camera.transform = view_transform(from,
			add(from, orientation), vector(0, 1, 0));
	return (true);
}

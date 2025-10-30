/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:35:58 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 03:51:38 by oostapen         ###   ########.fr       */
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
		parser_error("Camera: Orientation must be normalized (x²+y²+z²=1)",
			state->line_num);
}

static void	parse_cam_params(char *ptr, t_tuple *from,
				t_tuple *orient, t_parse_state *state)
{
	double	fov;

	if (!parse_vector3(&ptr, from))
		parser_error_cleanup(state, "Camera: Invalid position coordinates");
	if (!parse_vector3(&ptr, orient))
		parser_error_cleanup(state, "Camera: Invalid orientation vector");
	validate_camera_orientation(*orient, state);
	if (!parse_double(&ptr, &fov))
		parser_error_cleanup(state, "Camera: Invalid FOV value");
	if (fov <= 0 || fov > 180)
		parser_error("Camera: FOV must be > 0 and <= 180 degrees",
			state->line_num);
	if (!check_end_of_line(ptr))
		parser_error_cleanup(state, "Camera: Unexpected extra parameters");
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

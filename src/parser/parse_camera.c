/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:35:58 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 20:37:42 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	parse_camera(char *line, t_scene *scene)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;
	double	fov;
	
	/* Parse: "C 0,0,-5 0,0,1 70" */
	from = parse_vector3(&line);
	to = parse_vector3(&line);
	fov = parse_double(&line);
	
	/* Create camera with parsed FOV */
	scene->camera = camera_make(800, 600, fov * M_PI / 180.0);
	
	/* Set view transformation */
	up = vector(0, 1, 0);  /* Default up vector */
	scene->camera.transform = view_transform(from, to, up);

	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:32:27 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 21:43:19 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "matrices.h"

/*
** apply_sphere_transform - Apply translation and scaling
*/
static t_sphere	apply_sphere_transform(t_sphere sp, t_tuple ctr, double diam)
{
	t_matrix	scale;
	t_matrix	translate;
	t_matrix	transform;
	double		radius;

	radius = diam / 2.0;
	scale = scaling(radius, radius, radius);
	translate = translation(ctr.x, ctr.y, ctr.z);
	transform = mat_mul(translate, scale);
	return (sphere_set_transform(sp, transform));
}

/*
** sp 0,0,0 2.0 255,0,0
**    ^     ^   ^
**    |     |   +-- RGB color (0-255)
**    |     +------ Diameter
**    +------------ Center position (x,y,z)
*/
/*
** skip_trailing - Check no extra arguments after parsed data
*/
static bool	check_end_of_line(char *ptr)
{
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	return (*ptr == '\0' || *ptr == '\n' || *ptr == '\r');
}

static bool	parse_sphere_params(char *ptr, t_tuple *center,
				double *diameter, t_tuple *color)
{
	if (!parse_vector3(&ptr, center))
		return (false);
	if (!parse_double(&ptr, diameter) || *diameter <= 0)
		return (false);
	if (!parse_color_rgb(&ptr, color))
		return (false);
	return (check_end_of_line(ptr));
}

bool	parse_sphere(char *line, t_scene *scene)
{
	char		*ptr;
	t_tuple		center;
	double		diameter;
	t_tuple		color;
	t_sphere	sphere;

	ptr = line + 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!parse_sphere_params(ptr, &center, &diameter, &color))
		return (false);
	sphere = sphere_create();
	sphere.material.color = color;
	sphere = apply_sphere_transform(sphere, center, diameter);
	return (world_add_sphere(&scene->world, sphere));
}

/*
** parse_sphere - Parse sphere object (stack-based with heap prep)
** Format: sp <x,y,z> <diameter> <R,G,B>
** Example: sp 0,0,20 20 255,0,0
**
** HEAP TRANSITION NOTE:
** This function is already heap-ready! It uses world_add_sphere()
** which will handle dynamic allocation when you switch to heap.
** No changes needed to this function during transition.
*/
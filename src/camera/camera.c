/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:23:43 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/08 23:03:14 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "tuples.h"
#include "matrices.h"
#include "transformations.h"

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		up_normalized;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	orientation;

	forward = substract_tuples(to, from);
	forward = normalize_vector(forward);
	up_normalized = normalize_vector(up);
	left = cross_product(forward, up_normalized);
	true_up = cross_product(left, forward);
	orientation = mat_identity();
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	orientation.data[2][0] = -forward.x;
	orientation.data[2][1] = -forward.y;
	orientation.data[2][2] = -forward.z;
	return (mat_mul(orientation, translation(-from.x, -from.y, -from.z)));
}

/* Set default transform to identity matrix */
/* Compute pixel size and canvas dimensions in world space */
/* Determine canvas dimensions based on aspect ratio */
/* Compute pixel size in world units */
t_camera	camera_make(int hsize, int vsize, double fov)
{
	t_camera	cam;
	double		half_view;
	double		aspect;

	cam.hsize = hsize;
	cam.vsize = vsize;
	cam.field_of_view = fov;
	cam.transform = mat_identity();
	half_view = tan(fov / 2.0);
	aspect = (double)hsize / (double)vsize;
	if (aspect >= 1.0)
	{
		cam.half_width = half_view;
		cam.half_height = half_view / aspect;
	}
	else
	{
		cam.half_width = half_view * aspect;
		cam.half_height = half_view;
	}
	cam.pixel_size = (cam.half_width * 2.0) / (double)hsize;
	return (cam);
}

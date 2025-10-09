/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:23:43 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/09 21:53:28 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "matrices.h"
#include "rays.h"
#include "tuples.h"
#include "transformations.h"

/*
Camera X Y Z and `view_transform();

forward is local −Z, 
left is local    +X, 
true_up is local +Y;
they are not “equal” to the world X/Y/Z
*/
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

/*
** Creates camera with specified resolution and field of view.
** Computes pixel size and canvas dimensions in world space.
** Canvas positioned 1 unit in front of camera (z = -1).
** Note: fov must be in RADIANS (use degrees_to_radians() if parsing from .rt).
*/
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

static t_tuple	calculate_pixel_position(t_camera *camera, int px, int py)
{
	double	x_offset;
	double	y_offset;
	double	world_x;
	double	world_y;

	x_offset = (px + 0.5) * camera->pixel_size;
	y_offset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - x_offset;
	world_y = camera->half_height - y_offset;
	return (point(world_x, world_y, -1));
}

t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	t_tuple		pixel;
	t_tuple		origin;
	t_tuple		direction;
	t_matrix	inverse_transform;
	bool		invertible;

	pixel = calculate_pixel_position(camera, px, py);
	origin = point(0, 0, 0);
	inverse_transform = mat_inverse(camera->transform, &invertible);
	pixel = mat_mul_tuple(inverse_transform, pixel);
	origin = mat_mul_tuple(inverse_transform, origin);
	direction = normalize_vector(substract_tuples(pixel, origin));
	return (ray(origin, direction));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:22:50 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/09 21:58:17 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <math.h>
# include "math_utils.h" // For angle conversions
# include "tuples.h"
# include "matrices.h"
# include "rays.h"
# include "world.h"

/*
** - hsize: horizontal resolution in pixels
** - vsize: vertical resolution in pixels
** - field_of_view: viewing angle in radians (how much camera can see)
** - transform: view transformation matrix (default: identity)
** - pixel_size: size of a single pixel in world units (computed)
** - half_width: half of canvas width in world units (computed)
** - half_height: half of canvas height in world units (computed)
**
** NB: pixel_size, half_width, half_height are computed during construction
** based on hsize, vsize, and field_of_view.
*/
typedef struct s_camera
{
	int			hsize;
	int			vsize;
	double		field_of_view;
	t_matrix	transform;
	double		pixel_size;
	double		half_width;
	double		half_height;
}				t_camera;

t_camera	camera_make(int hsize, int vsize, double fov);
t_ray		ray_for_pixel(t_camera *camera, int px, int py);

/*
forward = normalize(to - from) = (0, 0, -1)// Look direction
left = cross(forward, up) = (1, 0, 0) // Camera left
true_up = cross(left, forward) = (0, 1, 0) // Camera up
identity matrix
[1 0 0 0] ← left vector (camera X-axis)
[0 1 0 0] ← true_up vector (camera Y-axis)
[0 0 1 0] ← -forward vector (camera Z-axis, inverted!)
[0 0 0 1]

[left.x    left.y    left.z    0]
[true_up.x true_up.y true_up.z 0]
[-fwd.x    -fwd.y    -fwd.z    0]
[0         0         0         1]
*/
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up);

// Renders the world as seen from the camera 
// MLX instance pointer (for image_create)
// Returns:
// - Pointer to t_image containing the rendered scene
// - NULL on allocation failure
// NB: Returned image must be freed with image_destroy() when done
t_image		*render(void *mlx, t_camera camera, t_world *world);

#endif
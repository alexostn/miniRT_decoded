/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:23:43 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/07 22:40:17 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "tuples.h"
#include "matrices.h"
#include "transformations.h"

/*
** view_transform()
** Description: Computes the view transformation matrix that orients the world
** relative to the camera's position and viewing direction.
**
** Parameters:
** - from: camera position (eye point)
** - to: point at which the camera is looking
** - up: approximate "up" direction vector (doesn't need to be exact)
**
** Returns: 4x4 transformation matrix that orients the world for rendering
**
** Algorithm:
** 1. Compute forward vector (normalized direction from 'from' to 'to')
** 2. Compute left vector (cross product of forward and normalized up)
** 3. Compute true_up vector (cross product of left and forward)
** 4. Build orientation matrix from these three vectors
** 5. Multiply by translation to move world relative to camera */
/* Step 1: Compute forward vector (direction camera is looking) */
/* Step 2: Normalize the up vector */
/* Step 3: Compute left vector (perpendicular to forward and up) */
/* Step 4: Compute true up vector (perpendicular to left and forward) */
/* Step 5: Build orientation matrix from the three basis vectors */
/* Row 0: left vector */
/* Row 1: true_up vector */
/* Row 2: negative forward vector (camera looks down -Z axis) */
/* Step 6: Apply translation to move world relative to camera position */

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_orientation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:23:43 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/09 21:53:28 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static t_tuple	base_up_replacement(t_tuple forward)
{
	if (fabs(forward.y) > 0.9)
		return (vector(1, 0, 0));
	return (vector(0, 1, 0));
}

static t_tuple	compute_left(t_tuple forward, t_tuple up)
{
	t_tuple	up_norm;
	double	dot;

	up_norm = normalize_vector(up);
	dot = dot_product(forward, up_norm);
	if (fabs(fabs(dot) - 1.0) < 0.001)
		up_norm = base_up_replacement(forward);
	return (cross_product(forward, up_norm));
}

static t_matrix	build_orientation(t_tuple left, t_tuple forward)
{
	t_matrix	orientation;
	t_tuple		true_up;

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
	return (orientation);
}

t_matrix	compute_orientation(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	left;

	forward = normalize_vector(substract_tuples(to, from));
	left = compute_left(forward, up);
	return (build_orientation(left, forward));
}

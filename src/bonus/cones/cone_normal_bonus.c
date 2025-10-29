/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_normal_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:30:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 17:54:25 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones.h"
#include "matrices.h"
#include "defines.h"
#include <math.h>

/*
** cone_local_normal_at()
** Calculates the normal vector at a point on the cone in local (object) space
**
** Parameters:
** - cone: pointer to the cone
** - p: the point in local space
**
** Returns:
** - t_tuple: the normal vector (not normalized)
*/
t_tuple	cone_local_normal_at(t_cone *cone, t_tuple p)
{
	double	dist;
	double	y;
	double	radius_at_y;

	dist = p.x * p.x + p.z * p.z;
	if (p.y >= (cone->maximum - EPS))
	{
		radius_at_y = fabs(cone->maximum);
		if (dist <= radius_at_y * radius_at_y + EPS)
			return (vector(0, 1, 0));
	}
	if (p.y <= (cone->minimum + EPS))
	{
		radius_at_y = fabs(cone->minimum);
		if (dist <= radius_at_y * radius_at_y + EPS)
			return (vector(0, -1, 0));
	}
	y = sqrt(dist);
	if (p.y > 0)
		y = -y;
	return (vector(p.x, y, p.z));
}

/*
** cone_normal_at()
** Calculates the normal vector at a point on the cone in world space
**
** Parameters:
** - cone: pointer to the cone
** - world_point: the point in world space
**
** Returns:
** - t_tuple: the normal vector (normalized)
*/
t_tuple	cone_normal_at(t_cone *cone, t_tuple world_point)
{
	bool		ok;
	t_matrix	inv;
	t_tuple		local_point;
	t_tuple		local_normal;
	t_tuple		world_normal;

	inv = mat_inverse(cone->shape.transform, &ok);
	if (ok)
		local_point = mat_mul_tuple(inv, world_point);
	else
		local_point = world_point;
	local_normal = cone_local_normal_at(cone, local_point);
	inv = mat_inverse(cone->shape.transform, &ok);
	if (ok)
		world_normal = mat_mul_tuple(mat_transpose(inv), local_normal);
	else
		world_normal = local_normal;
	world_normal.w = 0.0;
	return (normalize_vector(world_normal));
}


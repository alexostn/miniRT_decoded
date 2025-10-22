/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:57:24 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 15:58:51 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinders.h"
#include "matrices.h"

t_tuple	cylinder_local_normal_at(t_cylinder *cyl, t_tuple p)
{
	double	dist;

	(void)cyl;
	dist = p.x * p.x + p.z * p.z;
	if (dist < 1.0 && p.y >= (cyl->maximum - EPS))
		return (vector(0, 1, 0));
	if (dist < 1.0 && p.y <= (cyl->minimum + EPS))
		return (vector(0, -1, 0));
	return (vector(p.x, 0, p.z));
}

t_tuple	cylinder_normal_at(t_cylinder *cyl, t_tuple world_point)
{
	bool		ok;
	t_matrix	inv;
	t_tuple		local_point;
	t_tuple		local_normal;
	t_tuple		world_normal;

	inv = mat_inverse(cyl->shape.transform, &ok);
	if (ok)
		local_point = mat_mul_tuple(inv, world_point);
	else
		local_point = world_point;
	local_normal = cylinder_local_normal_at(cyl, local_point);
	inv = mat_inverse(cyl->shape.transform, &ok);
	if (ok)
		world_normal = mat_mul_tuple(mat_transpose(inv), local_normal);
	else
		world_normal = local_normal;
	world_normal.w = 0.0;
	return (normalize_vector(world_normal));
}

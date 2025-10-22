/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:17:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 17:29:32 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "planes.h"

t_plane	plane_create(void)
{
	t_plane	p;

	p.shape = shape_create();
	return (p);
}

t_tuple	plane_local_normal_at(t_tuple local_point)
{
	(void)local_point;
	return (vector(0, 1, 0));
}

t_xs	plane_local_intersect(t_plane *p, t_ray local_ray)
{
	t_xs	xs;
	double	t;

	(void)p;
	xs = xs_create();
	if (fabs(local_ray.direction.y) < EPS)
		return (xs);
	{
		t = -local_ray.origin.y / local_ray.direction.y;
		xs = intersections_add(xs, intersection_create(t, p));
		return (xs);
	}
}

t_xs	plane_intersect(t_plane *p, t_ray r)
{
	t_ray	local_ray;

	local_ray = shape_transform_ray_to_local(&p->shape, r);
	return (plane_local_intersect(p, local_ray));
}

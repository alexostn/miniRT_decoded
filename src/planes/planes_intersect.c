/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:53:59 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 22:27:55 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "planes.h"
#include "rays.h"
#include "matrices.h"
#include "intersect.h"
#include <math.h>

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

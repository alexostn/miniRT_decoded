/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:23:53 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/03 01:37:26 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computations.h"
/*
** prepare_computations()
** Precompute useful data for shading an intersection
**
** Parameters:
** - i: intersection structure (t_intersection)
** - r: ray along which the intersection occurred (t_ray)
**
** Returns:
** - t_comps: structure with precomputed values (t, object, point, eyev, normalv)
*/
t_comps	prepare_computations_sphere(t_intersection i, t_ray r, t_sphere s)
{
	t_comps	comps;

	comps.t = i.t;
	comps.sphere = s;
	comps.point = ray_position(r, comps.t);
	comps.eyev = multiply_tuple_scalar(r.direction, -1);
	comps.normalv = sphere_normal_at(&comps.sphere, comps.point);
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside_hit = 1;
		comps.normalv = multiply_tuple_scalar(comps.normalv, -1);
	}
	else
		comps.inside_hit = 0;
	return (comps);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:23:53 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:47:04 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computations.h"
#include "world.h"
#include "spheres.h"
#include "planes.h"
#include "cylinders.h"
#include "cones.h"
#include "materials.h"
#include "computations_object_lookup.h"

/*
** prepare_computations()
** Precompute useful data for shading an intersection (generic object)
*/
t_comps	prepare_computations(t_world *world, t_intersection hit, t_ray r)
{
	t_comps	comps;

	comps.t = hit.t;
	comps.object = identify_object(world, hit.object);
	comps.material = extract_hit_material(comps.object);
	comps.point = ray_position(r, comps.t);
	comps.eyev = multiply_tuple_scalar(r.direction, -1);
	comps.normalv = object_normal_at(comps.object, comps.point);
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside_hit = true;
		comps.normalv = multiply_tuple_scalar(comps.normalv, -1);
	}
	else
		comps.inside_hit = false;
	comps.over_point = add(comps.point,
			multiply_tuple_scalar(comps.normalv, EPS));
	return (comps);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:09:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/21 12:09:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computations.h"
#include "world.h"

static t_object_ref	make_sphere_ref(void)
{
	t_object_ref	ref;

	ref.type = OBJ_SPHERE;
	ref.ptr = NULL;
	return (ref);
}

t_comps	prepare_computations_sphere(t_intersection i, t_ray r, t_sphere s)
{
	t_comps	comps;

	comps.t = i.t;
	comps.object = make_sphere_ref();
	comps.material = s.material;
	comps.point = ray_position(r, comps.t);
	comps.eyev = multiply_tuple_scalar(r.direction, -1);
	comps.normalv = sphere_normal_at(&s, comps.point);
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

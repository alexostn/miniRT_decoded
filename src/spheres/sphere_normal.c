/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:30:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/02 21:04:42 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include <math.h>

/*
** transform_normal_to_world_space()
** Transforms an object normal to world space using inverse-transpose
**
** Parameters:
** - s: pointer to the sphere
** - object_normal: normal in object space
**
** Returns:
** - t_tuple: normal in world space
*/
static t_tuple	transform_normal_to_world_space(t_sphere *s,
			t_tuple object_normal)
{
	t_tuple		world_normal;
	t_matrix	inv_transform;
	t_matrix	inv_transpose;
	bool		ok;

	if (!mat_equal(s->transform, mat_identity()))
	{
		inv_transform = mat_inverse(s->transform, &ok);
		if (ok)
		{
			inv_transpose = mat_transpose(inv_transform);
			world_normal = mat_mul_tuple(inv_transpose, object_normal);
		}
		else
		{
			world_normal = object_normal;
		}
	}
	else
	{
		world_normal = object_normal;
	}
	world_normal.w = 0.0;
	return (world_normal);
}

/*
** sphere_normal_at()
** Computes the normal vector at a point on the sphere surface
**
** For a unit sphere at origin, the normal is simply the point itself
** (normalized). For transformed spheres, we need to apply inverse-transpose.
**
** Parameters:
** - s: pointer to the sphere
** - world_point: point on sphere surface in world coordinates
**
** Returns:
** - t_tuple: normalized normal vector
*/
t_tuple	sphere_normal_at(t_sphere *s, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;

	object_point = transform_point_to_object_space(s, world_point);
	object_normal = object_point;
	world_normal = transform_normal_to_world_space(s, object_normal);
	return (normalize_vector(world_normal));
}

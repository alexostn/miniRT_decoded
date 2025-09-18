/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/19 10:00:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*
** sphere_create()
** Creates a new unit sphere centered at origin
**
** Returns:
** - t_sphere: new sphere with identity transformation
*/
t_sphere	sphere_create(void)
{
	t_sphere	sphere;

	sphere.transform = mat_identity();
	sphere.material = NULL;
	return (sphere);
}

/*
** sphere_set_transform()
** Sets the transformation matrix for a sphere
**
** Parameters:
** - s: sphere to modify
** - transform: transformation matrix to apply
**
** Returns:
** - t_sphere: sphere with new transformation
*/
t_sphere	sphere_set_transform(t_sphere s, t_matrix transform)
{
	s.transform = transform;
	return (s);
}

/*
** sphere_intersect()
** Computes intersections between a ray and a unit sphere
**
** Parameters:
** - s: pointer to the sphere
** - r: the ray to intersec
**
** Returns:
** - t_xs: collection of intersections (0, 1, or 2)
*/
t_xs	sphere_intersect(t_sphere *s, t_ray r)
{
	t_xs			xs;
	t_tuple			sphere_to_ray;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			t1;
	double			t2;
	bool			ok;
	t_matrix		inv_transform;
	t_intersection	i1;
	t_intersection	i2;

	xs = xs_create(0);
	if (!mat_equal(s->transform, mat_identity()))
	{
		inv_transform = mat_inverse(s->transform, &ok);
		if (ok)
			r = ray_transform(r, inv_transform);
	}
	sphere_to_ray = r.origin;
	a = r.direction.x * r.direction.x + r.direction.y * r.direction.y
		+ r.direction.z * r.direction.z;
	b = 2.0 * (r.direction.x * sphere_to_ray.x + r.direction.y * sphere_to_ray.y
		+ r.direction.z * sphere_to_ray.z);
	c = (sphere_to_ray.x * sphere_to_ray.x + sphere_to_ray.y * sphere_to_ray.y
		+ sphere_to_ray.z * sphere_to_ray.z) - 1.0;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (xs);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	i1 = intersection_create(t1, s);
	i2 = intersection_create(t2, s);
	if (t1 <= t2)
	{
		xs = intersections_add(xs, i1);
		xs = intersections_add(xs, i2);
	}
	else
	{
		xs = intersections_add(xs, i2);
		xs = intersections_add(xs, i1);
	}
	return (xs);
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
	bool		ok;
	t_matrix	inv_transform;
	t_matrix	inv_transpose;

	if (!mat_equal(s->transform, mat_identity()))
	{
		inv_transform = mat_inverse(s->transform, &ok);
		if (ok)
			object_point = mat_mul_tuple(inv_transform, world_point);
		else
			object_point = world_point;
	}
	else
	{
		object_point = world_point;
	}
	object_normal = object_point;
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
	return (normalize_vector(world_normal));
}

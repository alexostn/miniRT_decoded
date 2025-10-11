/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:02:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/10 12:02:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinders.h"
#include <math.h>
#include "defines.h"

static int	approx_zero(double a)
{
	return (fabs(a) < EPS);
}

t_cylinder	cylinder_create(void)
{
	t_cylinder	c;

	c.shape = shape_create();
	c.minimum = -INFINITY;
	c.maximum = INFINITY;
	c.closed = false;
	return (c);
}

static int	check_cap(t_ray r, double t)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return ((x * x + z * z) <= 1.0 + EPS);
}

static void	intersect_caps(t_cylinder *cyl, t_ray r, t_xs *xs)
{
	double	t;

	if (!cyl->closed || approx_zero(r.direction.y))
		return ;
	/* lower cap */
	t = (cyl->minimum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
		*xs = intersections_add(*xs, intersection_create(t, cyl));
	/* upper cap */
	t = (cyl->maximum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
		*xs = intersections_add(*xs, intersection_create(t, cyl));
}

t_xs	cylinder_local_intersect(t_cylinder *cyl, t_ray local_ray)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t0;
	double	t1;
	t_xs	xs;
	double	y;

	xs = xs_create();
	a = local_ray.direction.x * local_ray.direction.x
		+ local_ray.direction.z * local_ray.direction.z;
	if (approx_zero(a))
	{
		intersect_caps(cyl, local_ray, &xs);
		return (xs);
	}
	b = 2.0 * local_ray.origin.x * local_ray.direction.x
		+ 2.0 * local_ray.origin.z * local_ray.direction.z;
	c = local_ray.origin.x * local_ray.origin.x
		+ local_ray.origin.z * local_ray.origin.z - 1.0;
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (xs);
	t0 = (-b - sqrt(disc)) / (2.0 * a);
	t1 = (-b + sqrt(disc)) / (2.0 * a);
	if (t0 > t1)
	{
		double tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	y = local_ray.origin.y + t0 * local_ray.direction.y;
	if (y > cyl->minimum && y < cyl->maximum)
		xs = intersections_add(xs, intersection_create(t0, cyl));
	y = local_ray.origin.y + t1 * local_ray.direction.y;
	if (y > cyl->minimum && y < cyl->maximum)
		xs = intersections_add(xs, intersection_create(t1, cyl));
	intersect_caps(cyl, local_ray, &xs);
	return (xs);
}

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

t_xs	cylinder_intersect(t_cylinder *cyl, t_ray r)
{
	t_ray	local_ray;

	local_ray = shape_transform_ray_to_local(&cyl->shape, r);
	return (cylinder_local_intersect(cyl, local_ray));
}

t_tuple	cylinder_normal_at(t_cylinder *cyl, t_tuple world_point)
{
	bool	 ok;
	t_matrix inv;
	t_tuple	 local_point;
	t_tuple	 local_normal;
	t_tuple	 world_normal;

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

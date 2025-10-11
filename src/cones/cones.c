/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:12:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/10 12:12:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones.h"
#include <math.h>
#include "defines.h"

static int	approx_zero(double a)
{
	return (fabs(a) < EPS);
}

t_cone	cone_create(void)
{
	t_cone c;

	c.shape = shape_create();
	c.minimum = -INFINITY;
	c.maximum = INFINITY;
	c.closed = false;
	return (c);
}

static int	check_cap_cone(t_ray r, double t, double y)
{
	double x = r.origin.x + t * r.direction.x;
	double z = r.origin.z + t * r.direction.z;
	double rad = fabs(y);
	return ((x * x + z * z) <= rad * rad + EPS);
}

static void	intersect_caps_cone(t_cone *cone, t_ray r, t_xs *xs)
{
	double t;

	if (!cone->closed || approx_zero(r.direction.y))
		return ;
	t = (cone->minimum - r.origin.y) / r.direction.y;
	if (check_cap_cone(r, t, cone->minimum))
		*xs = intersections_add(*xs, intersection_create(t, cone));
	t = (cone->maximum - r.origin.y) / r.direction.y;
	if (check_cap_cone(r, t, cone->maximum))
		*xs = intersections_add(*xs, intersection_create(t, cone));
}

t_xs	cone_local_intersect(t_cone *cone, t_ray local_ray)
{
	double a;
	double b;
	double c;
	double disc;
	t_xs  xs;

	xs = xs_create();
	a = local_ray.direction.x * local_ray.direction.x
		- local_ray.direction.y * local_ray.direction.y
		+ local_ray.direction.z * local_ray.direction.z;
	b = 2.0 * local_ray.origin.x * local_ray.direction.x
		- 2.0 * local_ray.origin.y * local_ray.direction.y
		+ 2.0 * local_ray.origin.z * local_ray.direction.z;
	c = local_ray.origin.x * local_ray.origin.x
		- local_ray.origin.y * local_ray.origin.y
		+ local_ray.origin.z * local_ray.origin.z;
    if (approx_zero(a) && approx_zero(b))
        return (xs);
    if (approx_zero(a) && !approx_zero(b))
    {
        double t = -c / b; /* linear case: b*t + c = 0 */
        xs = intersections_add(xs, intersection_create(t, cone));
        intersect_caps_cone(cone, local_ray, &xs);
        return (xs);
    }
    disc = b * b - 4.0 * a * c;
    if (disc < 0.0)
    {
        if (fabs(disc) < EPS)
            disc = 0.0;
        else
            return (xs);
    }
	{
		double t0 = (-b - sqrt(disc)) / (2.0 * a);
		double t1 = (-b + sqrt(disc)) / (2.0 * a);
		double y;
		if (t0 > t1)
		{
			double tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		y = local_ray.origin.y + t0 * local_ray.direction.y;
		if (y > cone->minimum && y < cone->maximum)
			xs = intersections_add(xs, intersection_create(t0, cone));
		y = local_ray.origin.y + t1 * local_ray.direction.y;
		if (y > cone->minimum && y < cone->maximum)
			xs = intersections_add(xs, intersection_create(t1, cone));
	}
	intersect_caps_cone(cone, local_ray, &xs);
	return (xs);
}

t_tuple	cone_local_normal_at(t_cone *cone, t_tuple p)
{
	double dist;

	(void)cone;
	dist = p.x * p.x + p.z * p.z;
	if (dist < 1.0 && p.y >= (cone->maximum - EPS))
		return (vector(0, 1, 0));
	if (dist < 1.0 && p.y <= (cone->minimum + EPS))
		return (vector(0, -1, 0));
	{
		double y = sqrt(p.x * p.x + p.z * p.z);
		if (p.y > 0)
			y = -y;
		return (vector(p.x, y, p.z));
	}
}

t_xs	cone_intersect(t_cone *cone, t_ray r)
{
	t_ray	local_ray;

	local_ray = shape_transform_ray_to_local(&cone->shape, r);
	return (cone_local_intersect(cone, local_ray));
}

t_tuple	cone_normal_at(t_cone *cone, t_tuple world_point)
{
	bool	 ok;
	t_matrix inv;
	t_tuple	 local_point;
	t_tuple	 local_normal;
t_tuple	 world_normal;

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

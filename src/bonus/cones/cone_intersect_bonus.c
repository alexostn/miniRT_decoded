/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersect_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:30:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/29 19:10:33 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones.h"
#include "math_utils.h"

/*
** intersect_caps_cone()
** Adds intersections with cone caps (top and bottom)
**
** Parameters:
** - cone: pointer to the cone
** - r: the ray (in local space)
** - xs: pointer to intersections collection
**
** Returns:
** - void
*/
static void	intersect_caps_cone(t_cone *cone, t_ray r, t_xs *xs)
{
	double	t;
	double	x;
	double	z;
	double	rad;

	if (!cone->closed || approx_zero(r.direction.y))
		return ;
	t = (cone->minimum - r.origin.y) / r.direction.y;
	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	rad = fabs(cone->minimum);
	if ((x * x + z * z) <= rad * rad + EPS)
		*xs = intersections_add(*xs, intersection_create(t, cone));
	t = (cone->maximum - r.origin.y) / r.direction.y;
	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	rad = fabs(cone->maximum);
	if ((x * x + z * z) <= rad * rad + EPS)
		*xs = intersections_add(*xs, intersection_create(t, cone));
}

/*
** add_cone_body_intersections()
** Adds intersections with cone body if within height range
**
** Parameters:
** - cone: pointer to the cone
** - ray: the ray (in local space)
** - xs: pointer to intersections collection
** - t: array with t0 and t1 values
**
** Returns:
** - void
*/
static void	add_cone_body_intersections(t_cone *cone,
				t_ray ray, t_xs *xs, double *t)
{
	double	y;
	double	tmp;

	if (t[0] > t[1])
	{
		tmp = t[0];
		t[0] = t[1];
		t[1] = tmp;
	}
	y = ray.origin.y + t[0] * ray.direction.y;
	if (y > cone->minimum && y < cone->maximum)
		*xs = intersections_add(*xs, intersection_create(t[0], cone));
	y = ray.origin.y + t[1] * ray.direction.y;
	if (y > cone->minimum && y < cone->maximum)
		*xs = intersections_add(*xs, intersection_create(t[1], cone));
}

/*
** handle_linear_case()
** Handles special case where a=0 (linear equation)
*/
static t_xs	handle_linear_case(t_cone *cone, t_ray r, double b, double c)
{
	t_xs	xs;
	double	t;

	xs = xs_create();
	if (approx_zero(b))
		return (xs);
	t = -c / b;
	xs = intersections_add(xs, intersection_create(t, cone));
	intersect_caps_cone(cone, r, &xs);
	return (xs);
}

/*
** cone_local_intersect()
** Solves the quadratic equation for cone-ray intersection in local space
**
** Parameters:
** - cone: pointer to the cone
** - r: the ray (already transformed to cone space)
**
** Returns:
** - t_xs: collection of intersections (0, 1, or 2)
*/
t_xs	cone_local_intersect(t_cone *cone, t_ray r)
{
	double	abc[3];
	double	t[2];
	t_xs	xs;

	xs = xs_create();
	abc[0] = r.direction.x * r.direction.x - r.direction.y * r.direction.y
		+ r.direction.z * r.direction.z;
	abc[1] = 2.0 * r.origin.x * r.direction.x - 2.0 * r.origin.y
		* r.direction.y + 2.0 * r.origin.z * r.direction.z;
	abc[2] = r.origin.x * r.origin.x - r.origin.y * r.origin.y
		+ r.origin.z * r.origin.z;
	if (approx_zero(abc[0]))
		return (handle_linear_case(cone, r, abc[1], abc[2]));
	abc[2] = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (abc[2] < 0.0 && fabs(abc[2]) > EPS)
		return (xs);
	if (abc[2] < 0.0)
		abc[2] = 0.0;
	t[0] = (-abc[1] - sqrt(abc[2])) / (2.0 * abc[0]);
	t[1] = (-abc[1] + sqrt(abc[2])) / (2.0 * abc[0]);
	add_cone_body_intersections(cone, r, &xs, t);
	intersect_caps_cone(cone, r, &xs);
	return (xs);
}

/*
** cone_intersect()
** Computes intersections between a ray and a cone
**
** Parameters:
** - cone: pointer to the cone
** - r: the ray to intersect
**
** Returns:
** - t_xs: collection of intersections (0, 1, or 2)
*/
t_xs	cone_intersect(t_cone *cone, t_ray r)
{
	t_ray	local_ray;

	local_ray = shape_transform_ray_to_local(&cone->shape, r);
	return (cone_local_intersect(cone, local_ray));
}

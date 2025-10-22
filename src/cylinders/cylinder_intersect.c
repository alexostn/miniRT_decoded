/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:52:09 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 16:54:46 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinders.h"
#include "math_utils.h"

/*
** intersect_caps()
** Adds intersections with cylinder caps (top and bottom)
**
** Parameters:
** - cyl: pointer to the cylinder
** - r: the ray (in local space)
** - xs: pointer to intersections collection
**
** Returns:
** - void
*/
static void	intersect_caps(t_cylinder *cyl, t_ray r, t_xs *xs)
{
	double	t;
	double	x;
	double	z;

	if (!cyl->closed || approx_zero(r.direction.y))
		return ;
	t = (cyl->minimum - r.origin.y) / r.direction.y;
	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	if ((x * x + z * z) <= 1.0 + EPS)
		*xs = intersections_add(*xs, intersection_create(t, cyl));
	t = (cyl->maximum - r.origin.y) / r.direction.y;
	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	if ((x * x + z * z) <= 1.0 + EPS)
		*xs = intersections_add(*xs, intersection_create(t, cyl));
}

/*
** calculate_cylinder_quadratic_coefficients()
** Calculates coefficients a, b, c for cylinder-ray intersection quadratic
**
** Parameters:
** - r: the ray (already transformed to cylinder space)
** - a: pointer to store coefficient a
** - b: pointer to store coefficient b
** - c: pointer to store coefficient c
**
** Returns:
** - void
*/
static void	calculate_cylinder_quadratic_coefficients(t_ray r,
				double *a, double *b, double *c)
{
	*a = r.direction.x * r.direction.x
		+ r.direction.z * r.direction.z;
	*b = 2.0 * r.origin.x * r.direction.x
		+ 2.0 * r.origin.z * r.direction.z;
	*c = r.origin.x * r.origin.x
		+ r.origin.z * r.origin.z - 1.0;
}

/*
** add_cylinder_body_intersections()
** Adds intersections with cylinder body (side surface) if within height range
**
** Parameters:
** - cyl: pointer to the cylinder
** - ray: the ray (in local space)
** - xs: pointer to intersections collection
** - t: array with t0 and t1 values
**
** Returns:
** - void
*/
static void	add_cylinder_body_intersections(t_cylinder *cyl,
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
	if (y > cyl->minimum && y < cyl->maximum)
		*xs = intersections_add(*xs, intersection_create(t[0], cyl));
	y = ray.origin.y + t[1] * ray.direction.y;
	if (y > cyl->minimum && y < cyl->maximum)
		*xs = intersections_add(*xs, intersection_create(t[1], cyl));
}

/*
** cylinder_local_intersect()
** Solves the quadratic equation for cylinder-ray intersection in local space
**
** Parameters:
** - cyl: pointer to the cylinder
** - r: the ray (already transformed to cylinder space)
**
** Returns:
** - t_xs: collection of intersections (0, 1, or 2)
*/
t_xs	cylinder_local_intersect(t_cylinder *cyl, t_ray r)
{
	double	abc[3];
	double	t[2];
	t_xs	xs;

	xs = xs_create();
	calculate_cylinder_quadratic_coefficients(r, &abc[0], &abc[1], &abc[2]);
	if (approx_zero(abc[0]))
	{
		intersect_caps(cyl, r, &xs);
		return (xs);
	}
	abc[2] = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (abc[2] < 0.0)
		return (xs);
	t[0] = (-abc[1] - sqrt(abc[2])) / (2.0 * abc[0]);
	t[1] = (-abc[1] + sqrt(abc[2])) / (2.0 * abc[0]);
	add_cylinder_body_intersections(cyl, r, &xs, t);
	intersect_caps(cyl, r, &xs);
	return (xs);
}

/*
** cylinder_intersect()
** Computes intersections between a ray and a cylinder
**
** Parameters:
** - cyl: pointer to the cylinder
** - r: the ray to intersect
**
** Returns:
** - t_xs: collection of intersections (0, 1, or 2)
*/
t_xs	cylinder_intersect(t_cylinder *cyl, t_ray r)
{
	t_ray	local_ray;

	local_ray = shape_transform_ray_to_local(&cyl->shape, r);
	return (cylinder_local_intersect(cyl, local_ray));
}

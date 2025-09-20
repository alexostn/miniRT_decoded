/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/20 14:48:51 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include <math.h>

/*
** add_intersections_sorted()
** Adds two intersections to the collection in sorted order
**
** Parameters:
** - xs: existing intersections collection
** - t1: first intersection t value
** - t2: second intersection t value
** - s: pointer to the sphere
**
** Returns:
** - t_xs: updated intersections collection
*/
static t_xs	add_intersections_sorted(t_xs xs, double t1, double t2, t_sphere *s)
{
	t_intersection	i1;
	t_intersection	i2;

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
** calculate_quadratic_coefficients()
** Calculates the coefficients a, b, c for the sphere-ray intersection quadratic
**
** Parameters:
** - r: the ray (already transformed to sphere space)
** - a: pointer to store coefficient a
** - b: pointer to store coefficient b  
** - c: pointer to store coefficient c
**
** Returns:
** - void
*/
static void	calculate_quadratic_coefficients(t_ray r, double *a, double *b, double *c)
{
	t_tuple	sphere_to_ray;

	sphere_to_ray = r.origin;
	*a = r.direction.x * r.direction.x + r.direction.y * r.direction.y
		+ r.direction.z * r.direction.z;
	*b = 2.0 * (r.direction.x * sphere_to_ray.x + r.direction.y * sphere_to_ray.y
		+ r.direction.z * sphere_to_ray.z);
	*c = (sphere_to_ray.x * sphere_to_ray.x + sphere_to_ray.y * sphere_to_ray.y
		+ sphere_to_ray.z * sphere_to_ray.z) - 1.0;
}

/*
** solve_quadratic_roots()
** Solves the quadratic equation and finds the intersection points
**
** Parameters:
** - a: coefficient a
** - b: coefficient b
** - c: coefficient c
** - t1: pointer to store first root
** - t2: pointer to store second root
**
** Returns:
** - bool: true if real roots exist, false otherwise
*/
static bool	solve_quadratic_roots(double a, double b, double c, double *t1, double *t2)
{
	double	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	*t1 = (-b - sqrt(discriminant)) / (2 * a);
	*t2 = (-b + sqrt(discriminant)) / (2 * a);
	return (true);
}

/*
** solve_sphere_quadratic()
** Solves the quadratic equation for sphere-ray intersection
**
** Parameters:
** - r: the ray (already transformed to sphere space)
** - s: pointer to the sphere
**
** Returns:
** - t_xs: collection of intersections (0, 1, or 2)
*/
static t_xs	solve_sphere_quadratic(t_ray r, t_sphere *s)
{
	t_xs	xs;
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;

	xs = xs_create(0);
	calculate_quadratic_coefficients(r, &a, &b, &c);
	if (!solve_quadratic_roots(a, b, c, &t1, &t2))
		return (xs);
	xs = add_intersections_sorted(xs, t1, t2, s);
	return (xs);
}

/*
** sphere_intersect()
** Computes intersections between a ray and a unit sphere
**
** Parameters:
** - s: pointer to the sphere
** - r: the ray to intersect
**
** Returns:
** - t_xs: collection of intersections (0, 1, or 2)
*/
t_xs	sphere_intersect(t_sphere *s, t_ray r)
{
	t_xs		xs;
	t_matrix	inv_transform;
	bool		ok;

	xs = xs_create(0);
	if (!mat_equal(s->transform, mat_identity()))
	{
		inv_transform = mat_inverse(s->transform, &ok);
		if (ok)
			r = ray_transform(r, inv_transform);
	}
	xs = solve_sphere_quadratic(r, s);
	return (xs);
}

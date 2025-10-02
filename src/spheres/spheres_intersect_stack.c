/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres_intersect_stack.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:11:34 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/02 17:10:13 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include <math.h>
#include <stdlib.h>

/*
** === STACK-SPECIFIC FUNCTIONS ===
** These functions work only with stack-based collections (t_xs_stack)
**
** === SECTION 1: Basic intersection utilities ===
*/

t_xs_stack	xs_create_stack(void)
{
	t_xs_stack	xs;

	xs.count = 0;
	xs.capacity = MAX_INTERSECTIONS;
	return (xs);
}

t_intersection	intersection_create_stack(double t, void *obj)
{
	t_intersection	intersection;

	intersection.t = t;
	intersection.object = obj;
	return (intersection);
}

/*
** === SECTION 3: Sphere intersection (replaces sphere_intersect.c) ===
**
**
** add_intersections_sorted_stack()
** Adds two intersections to the stack collection in sorted order
*/
bool	add_intersections_sorted_stack(t_xs_stack *xs, double t1,
				double t2, t_sphere *s)
{
	t_intersection	i1;
	t_intersection	i2;

	i1 = intersection_create_stack(t1, s);
	i2 = intersection_create_stack(t2, s);
	if (t1 <= t2)
	{
		xs_add_stack(xs, i1);
		xs_add_stack(xs, i2);
	}
	else
	{
		xs_add_stack(xs, i2);
		xs_add_stack(xs, i1);
	}
	return (true);
}

/*
** solve_sphere_quadratic_stack()
** Solves quadratic equation for sphere-ray intersection (STACK version)
** REUSES: calculate_quadratic_coefficients() and solve_quadratic_roots()
*/
t_xs_stack	solve_sphere_quadratic_stack(t_ray r, t_sphere *s)
{
	t_xs_stack			xs;
	t_quadratic_coeffs	coeffs;
	double				t1;
	double				t2;

	xs = xs_create_stack();
	calculate_quadratic_coefficients(r, &coeffs.a, &coeffs.b, &coeffs.c);
	if (!solve_quadratic_roots(coeffs, &t1, &t2))
		return (xs);
	add_intersections_sorted_stack(&xs, t1, t2, s);
	return (xs);
}

/*
** sphere_intersect_stack()
** Computes intersections between ray and sphere (STACK version)
** REUSES: Transformation logic identical to heap version
*/
t_xs_stack	sphere_intersect_stack(t_sphere *s, t_ray r)
{
	t_xs_stack	xs;
	t_matrix	inv_transform;
	bool		ok;

	xs = xs_create_stack();
	if (!mat_equal(s->transform, mat_identity()))
	{
		inv_transform = mat_inverse(s->transform, &ok);
		if (ok)
			r = ray_transform(r, inv_transform);
	}
	xs = solve_sphere_quadratic_stack(r, s);
	return (xs);
}

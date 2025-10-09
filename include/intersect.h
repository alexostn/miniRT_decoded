/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/09 16:23:39 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "spheres.h"
# include "image.h"
# define MAX_INTERSECTIONS 32

/*
** Intersection structure
** Represents a single intersection between a ray and an objec
*/
typedef struct s_intersection
{
	double	t;			// distance along the ray
	void	*object;	// pointer to the intersected objec
}	t_intersection;

/*
** Intersections collection
** Stores multiple intersections between a ray and objects
*/
typedef struct s_intersections
{
	int				count;
	int				capacity;
	t_intersection	intersections[MAX_INTERSECTIONS];
}	t_xs;

/*
** Quadratic coefficients structure
** Groups the three coefficients of a quadratic equation
*/
typedef struct s_quadratic_coeffs
{
	double	a;
	double	b;
	double	c;
}	t_quadratic_coeffs;

/*
** Intersection utilities
*/
t_xs			sphere_intersect(t_sphere *s, t_ray r);
t_xs			xs_create(void);
void			intersections_destroy(t_xs *xs);
t_xs			intersections_add(t_xs xs, t_intersection i);
int				intersections_count(t_xs xs);
t_intersection	intersection_create(double t, void *obj);
t_intersection	intersections_get(t_xs xs, int index);
t_intersection	intersections_hit(t_xs xs);

/*
** Intersection math utilities
*/
t_xs			solve_sphere_quadratic(t_ray r, t_sphere *s);
void			calculate_quadratic_coefficients(t_ray r,
					double *a, double *b, double *c);
bool			solve_quadratic_roots(t_quadratic_coeffs coeffs,
					double *t1, double *t2);

#endif

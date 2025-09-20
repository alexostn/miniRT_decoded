/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/19 10:00:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERES_H
# define SPHERES_H

# include "tuples.h"
# include "matrices.h"
# include "rays.h"

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
	int				count;			// number of intersections
	t_intersection	*intersections;	// array of intersections
}	t_xs;

/*
** Sphere structure
** Represents a unit sphere centered at origin
*/
typedef struct s_sphere
{
	t_matrix	transform;	// transformation matrix (identity by default)
	void		*material;	// material properties (placeholder for now)
}	t_sphere;

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
** Sphere creation and operations
*/
t_sphere		sphere_create(void);
t_sphere		sphere_set_transform(t_sphere s, t_matrix transform);
t_xs			sphere_intersect(t_sphere *s, t_ray r);
t_tuple			sphere_normal_at(t_sphere *s, t_tuple world_point);

/*
** Intersection utilities
*/

t_xs			xs_create(int count);
void			intersections_destroy(t_xs *xs);
t_xs			intersections_add(t_xs xs, t_intersection i);
int				intersections_count(t_xs xs);
t_intersection	intersection_create(double t, void *obj);
t_intersection	intersections_get(t_xs xs, int index);
t_intersection	intersections_hit(t_xs xs);

#endif

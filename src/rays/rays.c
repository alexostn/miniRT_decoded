/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/19 10:00:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"
#include "tuples.h"
#include "matrices.h"

/*
** ray()
** Create a new ray with given origin and direction
** 
** Parameters:
** - origin: starting point of the ray (should be a point with w=1)
** - direction: direction vector of the ray (should be a vector with w=0)
** 
** Returns:
** - new ray structure
*/
t_ray	ray(t_tuple origin, t_tuple direction)
{
	t_ray	new_ray;

	new_ray.origin = origin;
	new_ray.direction = direction;
	return (new_ray);
}

/*
** ray_position()
** Compute the position of a point along a ray at distance t
** Formula: position = origin + direction * t
** 
** Parameters:
** - r: the ray
** - t: distance along the ray
** 
** Returns:
** - point at distance t along the ray
*/
t_tuple	ray_position(t_ray r, double t)
{
	return (add(r.origin, multiply_tuple_scalar(r.direction, t)));
}

/*
** ray_transform()
** Transforms a ray by applying a transformation matrix
** 
** Parameters:
** - r: the ray to transform
** - m: transformation matrix to apply
** 
** Returns:
** - t_ray: new transformed ray
*/
t_ray	ray_transform(t_ray r, t_matrix m)
{
	t_ray	transformed_ray;

	// Transform the origin (point)
	transformed_ray.origin = mat_mul_tuple(m, r.origin);
	
	// Transform the direction (vector)
	// Note: direction is NOT normalized after transformation
	transformed_ray.direction = mat_mul_tuple(m, r.direction);
	
	return (transformed_ray);
}

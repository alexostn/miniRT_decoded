/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 18:36:35 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

/*
** intersection_create()
** Creates a new intersection with given t value and object pointer
**
** Parameters:
** - t: distance along the ray where intersection occurs
** - obj: pointer to the intersected objec
**
** Returns:
** - t_intersection: new intersection
*/
t_intersection	intersection_create(double t, void *obj)
{
	t_intersection	i;

	i.t = t;
	i.object = obj;
	return (i);
}

/*
** xs_create()
** Creates an empty intersections collection using static storage
**
** Returns:
** - t_xs: new intersections collection
*/
t_xs	xs_create(void)
{
	t_xs	xs;

	xs.count = 0;
	xs.capacity = MAX_INTERSECTIONS;
	return (xs);
}

/*
** intersections_destroy()
** Frees memory allocated for intersections collection
**
** Parameters:
** - xs: pointer to intersections collection to destroy
*/
void	intersections_destroy(t_xs *xs)
{
	if (!xs)
		return ;
	xs->count = 0;
}

/*
** intersections_count()
** Returns the number of intersections in the collection
**
** Parameters:
** - xs: intersections collection
**
** Returns:
** - int: number of intersections
*/
int	intersections_count(t_xs xs)
{
	return (xs.count);
}

/*
** intersections_get()
** Gets an intersection at a specific index
**
** Parameters:
** - xs: intersections collection
** - index: index of the intersection to ge
**
** Returns:
** - t_intersection: the intersection at the given index
**   Returns a null intersection if index is out of bounds
*/
t_intersection	intersections_get(t_xs xs, int index)
{
	t_intersection	null_intersection;

	null_intersection.t = -1.0;
	null_intersection.object = NULL;
	if (index < 0 || index >= xs.count)
		return (null_intersection);
	return (xs.intersections[index]);
}

/*
** intersections_add_all()
** Adds all intersections from one collection to another
*/
t_xs	intersections_add_all(t_xs xs, t_xs *to_add)
{
	int	i;

	i = 0;
	while (i < to_add->count)
	{
		xs = intersections_add(xs, to_add->intersections[i]);
		i++;
	}
	return (xs);
}

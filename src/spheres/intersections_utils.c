/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/19 10:00:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include <stdlib.h>

/*
** intersection_create()
** Creates a new intersection with given t value and object pointer
** 
** Parameters:
** - t: distance along the ray where intersection occurs
** - obj: pointer to the intersected object
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
** Creates a new intersections collection
** 
** Parameters:
** - count: initial number of intersections
** 
** Returns:
** - t_xs: new intersections collection
*/
t_xs	xs_create(int count)
{
	t_xs	xs;

	xs.count = 0;
	xs.intersections = NULL;
	if (count > 0)
	{
		xs.intersections = malloc(count * sizeof(t_intersection));
		if (xs.intersections)
			xs.count = count;
	}
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
	if (xs && xs->intersections)
	{
		free(xs->intersections);
		xs->intersections = NULL;
		xs->count = 0;
	}
}

/*
** intersections_add()
** Adds a new intersection to the collection, maintaining sorted order by t
** 
** Parameters:
** - xs: existing intersections collection
** - i: intersection to add
** 
** Returns:
** - t_xs: new intersections collection with added intersection (sorted by t)
*/
t_xs	intersections_add(t_xs xs, t_intersection i)
{
	t_xs			new_xs;
	t_intersection	*new_intersections;
	int				new_count;
	int				insert_pos;
	int				j;

	new_count = xs.count + 1;
	new_intersections = malloc(new_count * sizeof(t_intersection));
	if (!new_intersections)
		return (xs); // Return original if allocation fails

	// Find insertion position to maintain sorted order (ascending by t)
	insert_pos = 0;
	while (insert_pos < xs.count && xs.intersections[insert_pos].t < i.t)
		insert_pos++;

	// Copy existing intersections before insertion point
	for (j = 0; j < insert_pos; j++)
		new_intersections[j] = xs.intersections[j];

	// Insert new intersection
	new_intersections[insert_pos] = i;

	// Copy remaining intersections after insertion point
	for (j = insert_pos; j < xs.count; j++)
		new_intersections[j + 1] = xs.intersections[j];

	// Free old memory
	if (xs.intersections)
		free(xs.intersections);

	// Create new collection
	new_xs.count = new_count;
	new_xs.intersections = new_intersections;

	return (new_xs);
}

/*
** intersections_hit()
** Finds the intersection with the smallest positive t value
** 
** Parameters:
** - xs: intersections collection
** 
** Returns:
** - t_intersection: the hit intersection, or NULL intersection if no hit
*/
t_intersection	intersections_hit(t_xs xs)
{
	t_intersection	hit;
	
	// Initialize as "no hit"
	hit.t = -1.0;
	hit.object = NULL;
	
	// Since intersections are sorted by t (ascending),
	// the first positive t is the hit
	for (int i = 0; i < xs.count; i++)
	{
		if (xs.intersections[i].t >= 0)
		{
			hit = xs.intersections[i];
			break; // Found the first positive t, we're done!
		}
	}
	
	return (hit);
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
** - index: index of the intersection to get
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

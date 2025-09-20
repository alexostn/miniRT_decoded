/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/20 14:48:51 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include <stdlib.h>

/*
** intersections_add()
** Adds a new intersection to the collection, maintaining sorted order by
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
		return (xs);
	insert_pos = 0;
	while (insert_pos < xs.count && xs.intersections[insert_pos].t < i.t)
		insert_pos++;
	j = 0;
	while (j < insert_pos)
	{
		new_intersections[j] = xs.intersections[j];
		j++;
	}
	new_intersections[insert_pos] = i;
	j = insert_pos;
	while (j < xs.count)
	{
		new_intersections[j + 1] = xs.intersections[j];
		j++;
	}
	if (xs.intersections)
		free(xs.intersections);
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
** - t_intersection: the hit intersection, or NULL intersection if no hi
*/
t_intersection	intersections_hit(t_xs xs)
{
	t_intersection	hit;
	int				i;

	hit.t = -1.0;
	hit.object = NULL;
	i = 0;
	while (i < xs.count)
	{
		if (xs.intersections[i].t >= 0)
		{
			hit = xs.intersections[i];
			break ;
		}
		i++;
	}
	return (hit);
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

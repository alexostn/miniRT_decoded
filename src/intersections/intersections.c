/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/09 16:14:19 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include <stddef.h>
#include "intersect.h"

/*
** find_insertion_position()
** Finds the correct position to insert a new intersection 
** to maintain sorted order
**
** Parameters:
** - xs: existing intersections collection
** - i: intersection to add
**
** Returns:
** - int: position where the intersection should be inserted
*/
static int	find_insertion_position(t_xs xs, t_intersection i)
{
	int	insert_pos;

	insert_pos = 0;
	while (insert_pos < xs.count && xs.intersections[insert_pos].t < i.t)
		insert_pos++;
	return (insert_pos);
}

/*
** create_sorted_intersections_array()
** Creates a new sorted intersections array by copying existing intersections
** and inserting the new intersection at the correct position
**
** Parameters:
** - xs: existing intersections collection
** - new_intersections: destination array
** - i: intersection to insert
** - insert_pos: position where to insert the intersection
**
** Returns:
** - void
*/
static void	insert_intersection(t_xs *xs, t_intersection i, int insert_pos)
{
	int	j;

	j = xs->count;
	while (j > insert_pos)
	{
		xs->intersections[j] = xs->intersections[j - 1];
		j--;
	}
	xs->intersections[insert_pos] = i;
	xs->count++;
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
	int				insert_pos;

	if (xs.count >= xs.capacity)
		return (xs);
	insert_pos = find_insertion_position(xs, i);
	insert_intersection(&xs, i, insert_pos);
	return (xs);
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

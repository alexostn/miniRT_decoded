/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects_collection_stack.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:22:08 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/30 15:37:01 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include <math.h>
#include <stdlib.h>

/*
** === STACK-SPECIFIC FUNCTIONS ===
** These functions work only with stack-based collections (t_xs_stack)
**
** === SECTION 2: Collection management
**		(extention for spheres_intersect_stack.c) ===
*/
int	intersections_count_stack(t_xs_stack xs)
{
	return (xs.count);
}

/*
Find insertion position to maintain sorted order
	insert_pos = 0;
Shift elements to make space
	j = xs->count;
Insert new intersection
	xs->intersections[insert_pos] = i;
*/
bool	xs_add_stack(t_xs_stack *xs, t_intersection i)
{
	int	insert_pos;
	int	j;

	if (!xs || xs->count >= xs->capacity)
		return (false);
	insert_pos = 0;
	while (insert_pos < xs->count && xs->intersections[insert_pos].t < i.t)
		insert_pos++;
	j = xs->count;
	while (j > insert_pos)
	{
		xs->intersections[j] = xs->intersections[j - 1];
		j--;
	}
	xs->intersections[insert_pos] = i;
	xs->count++;
	return (true);
}

t_intersection	intersections_get_stack(t_xs_stack xs, int index)
{
	t_intersection	empty;

	if (index < 0 || index >= xs.count)
	{
		empty.t = 0.0;
		empty.object = NULL;
		return (empty);
	}
	return (xs.intersections[index]);
}

/* Since array is sorted, first non-negative t is the hit i < */
t_intersection	intersections_hit_stack(t_xs_stack xs)
{
	t_intersection	no_hit;
	int				i;

	no_hit.t = -1.0;
	no_hit.object = NULL;
	if (xs.count == 0)
		return (no_hit);
	i = 0;
	while (i < xs.count)
	{
		if (xs.intersections[i].t >= 0.0)
			return (xs.intersections[i]);
		i++;
	}
	return (no_hit);
}

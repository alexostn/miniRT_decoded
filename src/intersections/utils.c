/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/20 14:49:16 by sarherna         ###   ########.fr       */
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

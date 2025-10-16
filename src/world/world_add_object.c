/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_add_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:24:34 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 23:37:38 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

/*
** world_add_sphere - Add sphere to world (stack version)
** @world: Pointer to world structure
** @sphere: Sphere to add
**
** Returns: true on success, false if world is full
**
** HEAP TRANSITION NOTE:
** When switching to heap-based world, replace with:
**   - Check if world->spheres_count >= world->capacity
**   - If full, realloc world->spheres array (double capacity)
**   - Then add sphere to array
** See docs/ARCHITECTURE.md for full transition guide
*/
bool	world_add_sphere(t_world *world, t_sphere sphere)
{
	if (!world)
		return (false);
	if (world->spheres_count >= MAX_OBJECTS)
		return (false);
	world->spheres[world->spheres_count] = sphere;
	world->spheres_count++;
	return (true);
}

/*
**
** This is a wrapper around world_add_sphere for consistency with parser.
** When multiple object types are added (planes, cylinders), this function
** will need to accept a generic t_object union/enum instead.
*/
bool	world_add_object(t_world *world, t_sphere sphere)
{
	return (world_add_sphere(world, sphere));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_add_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:24:34 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:51:57 by oostapen         ###   ########.fr       */
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
	if (world->spheres_count >= MAX_OBJECTS)
		return (false);
	world->spheres[world->spheres_count] = sphere;
	world->spheres_count++;
	return (true);
}

bool	world_add_plane(t_world *world, t_plane plane)
{
	if (world->planes_count >= MAX_OBJECTS)
		return (false);
	world->planes[world->planes_count] = plane;
	world->planes_count++;
	return (true);
}

bool	world_add_cylinder(t_world *world, t_cylinder cylinder)
{
	if (world->cylinders_count >= MAX_OBJECTS)
		return (false);
	world->cylinders[world->cylinders_count] = cylinder;
	world->cylinders_count++;
	return (true);
}

bool	world_add_cone(t_world *world, t_cone cone)
{
	if (world->cones_count >= MAX_OBJECTS)
		return (false);
	world->cones[world->cones_count] = cone;
	world->cones_count++;
	return (true);
}

/*
** world_add_object is now just an alias for world_add_sphere
** for backward compatibility with the parser.
** In a future refactor, the parser should call world_add_sphere directly.
*/
bool	world_add_object(t_world *world, t_sphere sphere)
{
	return (world_add_sphere(world, sphere));
}

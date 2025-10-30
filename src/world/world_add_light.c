/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_add_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 04:52:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:51:43 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

/*
** world_add_light - Add light source to world
** @world: Pointer to world structure
** @light: Light source to add
**
** Returns: true on success, false if world is full
**
** Used for bonus multi-light support.
** Allows multiple light sources in the scene.
*/
bool	world_add_light(t_world *world, t_point_light light)
{
	if (world->lights_count >= MAX_OBJECTS)
		return (false);
	world->lights[world->lights_count] = light;
	world->lights_count++;
	return (true);
}

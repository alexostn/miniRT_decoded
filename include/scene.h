/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:25:43 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 23:03:26 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "world.h"
# include "camera.h"

/*
t_scene - Complete scene configuration (stack-based)
world with objects and lighting (stack-based, includes ambient light)
camera configuration

Note: Ambient light properties are stored in world.ambient_color and
world.ambient_ratio to avoid duplication.
*/
typedef struct s_scene
{
	t_world		world;
	t_camera	camera;
}	t_scene;

void	init_scene(t_scene *scene);

#endif

/*
Initializes t_world on stack via world_make()
When switching to heap, change to t_world *world

1. Replace world_make() with world_create(initial_capacity)
2. Add error handling for allocation failures
3. Add corresponding scene_destroy() function
*/
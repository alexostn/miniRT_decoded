/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:25:43 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 19:31:26 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "world.h"
# include "camera.h"
# include "tuples.h"

/*
t_scene - Complete scene configuration (stack-based)
world with objects and lighting (stack-based)
camera configuration
cambient_color: (RGB 0-1)
ambient_ratio: Ambient intensity (0-1)
*/
typedef struct s_scene
{
	t_world		world;
	t_camera	camera;
	t_tuple		ambient_color;
	double		ambient_ratio;
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
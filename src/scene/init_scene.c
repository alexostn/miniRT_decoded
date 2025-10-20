/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:22:44 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 23:27:04 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "tuples.h"
#include "camera.h"

void	init_scene(t_scene *scene)
{
	if (!scene)
		return ;
	scene->world = world_make();
	scene->camera = camera_make(800, 600, M_PI / 3.0);
	scene->ambient_color = tuple(1, 1, 1, 1);
	scene->ambient_ratio = 0.1;
}

/*
init_scene - Initialize scene with default values
@scene: Pointer to scene structure to initialize
**
STACK VERSION (current):
- Initializes world via world_make() (stack-based)
- Sets default camera at origin looking down +Z
- Sets default ambient light (white, 10% intensity)
**
HEAP TRANSITION NOTE:
When switching to heap-based world:
1. Replace world_make() with world_create(initial_capacity)
2. Add error handling: if (!scene->world) exit
3. Add scene_destroy() to free world resources

HEAP VERSION (commented out for future use):
**
When you switch to heap-based world, uncomment and modify:
**
void init_scene(t_scene *scene)
{
    if (!scene)
        return ;
    
    // Allocate world on heap with initial capacity
    scene->world = world_create(10);  // Start with capacity for 10 objects
    if (!scene->world)
    {
        write(2, "Error\nFailed to allocate world\n", 32);
        exit(1);
    }
...
}
**
// Don't forget to add:
void scene_destroy(t_scene *scene)
{
    if (!scene)
        return ;
    world_destroy(scene->world);
}
*/
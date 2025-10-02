/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:27:40 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/02 16:37:36 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include <stddef.h>
# include "tuples.h"
# include "matrices.h"
# include "rays.h"
# include "lights.h"
# include "objects.h"// for future generic t_object definition

// Maximum number of objects for the STACK-BASED version
# define MAX_OBJECTS 32
// Optional wrapper for the light source.
// Current design: efficient STACK allocation	(t_light val)
// Future scaling: change to HEAP allocation	(t_light *val)
// with malloc/free if lights become numerous or large,
// without changing the external API
typedef struct s_opt_light
{
	bool	present;
	t_light	val;
}	t_opt_light;

// World structure containing all scene elements
// t_object	objects[MAX_OBJECTS]; //STACK-BASED
// - point to t_sphere and other objects for renderer
// typedef struct s_world
// {
// 	t_opt_light	light;		// Optional light source	
// 	t_sphere	spheres[MAX_OBJECTS];
// 	int			count;		// Current number of objects
// }	t_world;

// t_world	world_make(void);

#endif

//light.present bool could be used like that:
//TEST_ASSERT(!w.light.present, "world has no light")

/*
** --- HEAP EXPANSION SCENARIO ---
** int			capacity;
** t_object		**objects_ptr;
** When the scene becomes dynamic (e.g., objects added/removed at runtime)
*/
/*
typedef struct s_world
{
	t_opt_light	light;		// Optional light source
	void		**objects;	// Dynamic array of pointers to objects
	int			count;		// Current number of objects
	int			capacity;	// Capacity for the dynamic array
}	t_world;

// HEAP-BASED functions (since we're using dynamic arrays)
t_world	*world_create(int initial_capacity);
t_world	*default_world_create(void);
void	world_destroy(t_world *w);
*/

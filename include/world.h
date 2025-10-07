/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:27:40 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/07 17:15:46 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include <stddef.h>
# include "spheres.h"
# include "tuples.h"
# include "matrices.h"
# include "transformations.h"
# include "computations.h"
# include "rays.h"
# include "lights.h"
# include "objects.h"// for future generic t_object definition

# define MAX_OBJECTS 32

//Checks if light is present not just black '0'
typedef struct s_opt_light
{
	bool	present;
	t_light	val;
}	t_opt_light;

typedef struct s_shadow_check
{
	t_tuple			vector_to_light;
	double			distance;
	t_tuple			direction;
	t_ray			shadow_ray;
	t_xs			intersections;
	t_intersection	hit;
}	t_shadow_check;

/* ======  World Structure with Typed Object Arrays ====== */
// TODO:
// t_plane			planes[MAX_OBJECTS];
// int				planes_count;
// t_cylinder		cylinders[MAX_OBJECTS];
// int				cylinders_count;
// explicit presence flag is for:
// "0" - is this absence of light or black light?
typedef struct s_world
{
	bool			light_present; // explicit presence flag 
	t_point_light	light;
	t_sphere		spheres[MAX_OBJECTS];
	int				spheres_count;
}	t_world;

t_world		world_make(void);
t_world		default_world(void);
t_xs		intersect_world(t_world *w, t_ray r);
bool		is_shadowed(t_world world, t_tuple point);

t_tuple		color_at(t_world *w, t_ray r);
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

// HEAP-BASED functions (dynamic arrays)
t_world	*world_create(int initial_capacity);
t_world	*default_world_create(void);
void	world_destroy(t_world *w);
*/

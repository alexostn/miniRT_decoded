/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:27:40 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 18:36:35 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include <stddef.h>
# include "spheres.h"
# include "planes.h"
# include "cylinders.h"
# include "tuples.h"
# include "matrices.h"
# include "transformations.h"
# include "rays.h"
# include "lights.h"
# include "intersect.h"

# define MAX_OBJECTS 32

//Checks if light is present not just black '0'
// typedef struct s_opt_light
// {
// 	bool	present;
// 	t_light	val;
// }	t_opt_light;

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
// explicit presence flag is for:
// "0" - is this absence of light or black light?
typedef struct s_world
{
	bool			light_present; // explicit presence flag 
	t_point_light	light;
	t_sphere		spheres[MAX_OBJECTS];
	int				spheres_count;
	t_plane			planes[MAX_OBJECTS];
	int				planes_count;
	t_cylinder		cylinders[MAX_OBJECTS];
	int				cylinders_count;
}	t_world;

t_world		world_make(void);
t_world		default_world(void);
t_xs		intersect_world(t_world *w, t_ray r);
bool		is_shadowed(t_world world, t_tuple point);

t_tuple		color_at(t_world *w, t_ray r);

// typedef struct s_world	t_scene;

/*
** STACK VERSION (current):
**   Returns false if MAX_OBJECTS reached
**
** HEAP VERSION (future):
**   Reallocates array if capacity reached
**   Returns false only on malloc failure
*/
bool		world_add_sphere(t_world *world, t_sphere sphere);
bool		world_add_plane(t_world *world, t_plane plane);
bool		world_add_cylinder(t_world *world, t_cylinder cylinder);

/* Alias for parser compatibility (calls world_add_sphere) */
bool		world_add_object(t_world *world, t_sphere sphere);

#endif

/*
** --- HEAP EXPANSION SCENARIO ---
** int			capacity;
** t_object		**objects_ptr;
** When the scene becomes dynamic (e.g., objects added/removed at runtime)
**
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

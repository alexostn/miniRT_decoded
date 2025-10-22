/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:29:33 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 18:36:35 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "intersect.h"
#include "computations.h"

// --------------- STATIC MEMORY VERSION ----------------
// Note: w.light.val doesn't need initialization when present=false
// Note: spheres array doesn't need initialization for empty world
// TODO:
// w.planes_count = 0;
// w.cylinders_count = 0;
t_world	world_make(void)
{
	t_world	w;

	w.light_present = false;
	w.light.position = tuple(0, 0, 0, 0);
	w.light.intensity = tuple(0, 0, 0, 0);
	w.spheres_count = 0;
	w.planes_count = 0;
	w.cylinders_count = 0;
	return (w);
}

// Initializes empty world
// Set up light
// Create first sphere (outer) with custom material
// Create second sphere (inner) with scaling
t_world	default_world(void)
{
	t_world			w;
	t_material		m1;

	w = world_make();
	w.light_present = true;
	w.light.position = point(-10, 10, -10);
	w.light.intensity = point(1, 1, 1);
	w.spheres[0] = sphere_create();
	m1 = material_create();
	m1.color = point(0.8, 1.0, 0.6);
	m1.diffuse = 0.7;
	m1.specular = 0.2;
	w.spheres[0].material = m1;
	w.spheres[0].transform = mat_identity();
	w.spheres[1] = sphere_create();
	w.spheres[1].material = material_create();
	w.spheres[1].transform = scaling(0.5, 0.5, 0.5);
	w.spheres_count = 2;
	return (w);
}

//TODO: Iterate through all objects in world
t_xs	intersect_world(t_world *w, t_ray r)
{
	t_xs	result;
	t_xs	temp;
	int		i;

	result = xs_create();
	i = -1;
	while (++i < w->spheres_count)
	{
		temp = sphere_intersect(&w->spheres[i], r);
		result = intersections_add_all(result, &temp);
		intersections_destroy(&temp);
	}
	i = -1;
	while (++i < w->planes_count)
	{
		temp = plane_intersect(&w->planes[i], r);
		result = intersections_add_all(result, &temp);
		intersections_destroy(&temp);
	}
	i = -1;
	while (++i < w->cylinders_count)
	{
		temp = cylinder_intersect(&w->cylinders[i], r);
		result = intersections_add_all(result, &temp);
		intersections_destroy(&temp);
	}
	return (result);
}

bool	is_shadowed(t_world world, t_tuple point)
{
	t_shadow_check	calc;
	bool			shadowed;

	if (!world.light_present)
		return (false);
	calc.vector_to_light = substract_tuples(world.light.position, point);
	calc.distance = magnitude_of_vector(calc.vector_to_light);
	calc.direction = normalize_vector(calc.vector_to_light);
	calc.shadow_ray = ray(point, calc.direction);
	calc.intersections = intersect_world(&world, calc.shadow_ray);
	calc.hit = intersections_hit(calc.intersections);
	shadowed = (calc.hit.object != NULL && calc.hit.t < calc.distance);
	intersections_destroy(&calc.intersections);
	return (shadowed);
}

/*
**   - w: pointer to world (stack or heap)
**   - r: ray to trace
** Returns: color tuple (with w=0.0 for valid RGB)
** Note: This is the public API used by render() and tests.
**       Internally calls shade_hit() with shadow calculations.
** HEAP_READY: Works with both stack (world_make) and heap (world_create)
*/
t_tuple	color_at(t_world *w, t_ray r)
{
	t_xs			xs;
	t_intersection	hit;
	t_tuple			result;
	t_sphere		*object;
	t_comps			comps;

	xs = intersect_world(w, r);
	hit = intersections_hit(xs);
	if (!hit.object)
	{
		intersections_destroy(&xs);
		return (color_d(0.0, 0.0, 0.0));
	}
	object = (t_sphere *)hit.object;
	comps = prepare_computations_sphere(hit, r, *object);
	result = shade_hit(*w, comps);
	intersections_destroy(&xs);
	return (result);
}

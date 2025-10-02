/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:29:33 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/02 18:51:17 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

// --------------- STACK VERSION ----------------
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
t_xs_stack	intersect_world_stack(t_world *w, t_ray r)
{
	t_xs_stack	result;
	t_xs_stack	temp;
	int			i;
	int			j;

	result = xs_create_stack();
	i = 0;
	while (i < w->spheres_count)
	{
		temp = sphere_intersect_stack(&w->spheres[i], r);
		j = 0;
		while (j < temp.count)
		{
			xs_add_stack(&result, temp.intersections[j]);
			j++;
		}
		i++;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:23:53 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:47:04 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computations.h"
#include "world.h"
#include "spheres.h"
#include "planes.h"
#include "cylinders.h"
#include "cones.h"
#include "materials.h"

static t_object_ref	identify_object(t_world *world, void *ptr)
{
	t_object_ref	ref;
	int				i;

	ref.type = OBJ_UNKNOWN;
	ref.ptr = ptr;
	if (!ptr || !world)
		return (ref);
	i = 0;
	while (i < world->spheres_count)
	{
		if ((void *)&world->spheres[i] == ptr)
		{
			ref.type = OBJ_SPHERE;
			return (ref);
		}
		i++;
	}
	i = 0;
	while (i < world->planes_count)
	{
		if ((void *)&world->planes[i] == ptr)
		{
			ref.type = OBJ_PLANE;
			return (ref);
		}
		i++;
	}
	i = 0;
	while (i < world->cylinders_count)
	{
		if ((void *)&world->cylinders[i] == ptr)
		{
			ref.type = OBJ_CYLINDER;
			return (ref);
		}
		i++;
	}
	i = 0;
	while (i < world->cones_count)
	{
		if ((void *)&world->cones[i] == ptr)
		{
			ref.type = OBJ_CONE;
			return (ref);
		}
		i++;
	}
	return (ref);
}

static t_material	extract_material(t_object_ref ref)
{
	t_material	default_material;

	default_material = material_create();
	if (ref.type == OBJ_SPHERE)
		return (((t_sphere *)ref.ptr)->material);
	if (ref.type == OBJ_PLANE)
		return (((t_plane *)ref.ptr)->shape.material);
	if (ref.type == OBJ_CYLINDER)
		return (((t_cylinder *)ref.ptr)->shape.material);
	if (ref.type == OBJ_CONE)
		return (((t_cone *)ref.ptr)->shape.material);
	return (default_material);
}

static t_tuple	object_normal_at(t_object_ref ref, t_tuple world_point)
{
	if (ref.type == OBJ_SPHERE)
		return (sphere_normal_at((t_sphere *)ref.ptr, world_point));
	if (ref.type == OBJ_PLANE)
		return (plane_normal_at((t_plane *)ref.ptr, world_point));
	if (ref.type == OBJ_CYLINDER)
		return (cylinder_normal_at((t_cylinder *)ref.ptr, world_point));
	if (ref.type == OBJ_CONE)
		return (cone_normal_at((t_cone *)ref.ptr, world_point));
	return (vector(0, 0, 0));
}

/*
** prepare_computations()
** Precompute useful data for shading an intersection (generic object)
*/
t_comps	prepare_computations(t_world *world, t_intersection hit, t_ray r)
{
	t_comps	comps;

	comps.t = hit.t;
	comps.object = identify_object(world, hit.object);
	comps.material = extract_material(comps.object);
	comps.point = ray_position(r, comps.t);
	comps.eyev = multiply_tuple_scalar(r.direction, -1);
	comps.normalv = object_normal_at(comps.object, comps.point);
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside_hit = true;
		comps.normalv = multiply_tuple_scalar(comps.normalv, -1);
	}
	else
		comps.inside_hit = false;
	comps.over_point = add(comps.point,
			multiply_tuple_scalar(comps.normalv, EPS));
	return (comps);
}

t_tuple	shade_hit(t_world world, t_comps comps)
{
	t_lighting_args	args;
	t_tuple			final_color;
	bool			in_shadow;
	int				i;
	t_tuple			ambient;
	double			ambient_coeff;
	t_material		material_copy;

	ambient = color_d(0, 0, 0);
	if (world.ambient_ratio > 0.0)
	{
		ambient_coeff = comps.material.ambient * world.ambient_ratio;
		ambient = multiply_tuple_scalar(
				multiply_tuples(comps.material.color,
					world.ambient_color),
				ambient_coeff);
	}
	final_color = ambient;
	i = 0;
	while (i < world.lights_count)
	{
		material_copy = comps.material;
		material_copy.ambient = 0.0;
		args.material = material_copy;
		args.light = world.lights[i];
		args.position = comps.over_point;
		args.eyev = comps.eyev;
		args.normalv = comps.normalv;
		in_shadow = is_shadowed(world, comps.over_point, world.lights[i]);
		args.in_shadow = in_shadow;
		final_color = add(final_color, lighting(args));
		i++;
	}
	return (final_color);
}

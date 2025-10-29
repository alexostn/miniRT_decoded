/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_support_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:38:07 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/26 20:38:28 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computations_object_lookup.h"
#include "materials.h"
#include "lights.h"

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

t_material	extract_hit_material(t_object_ref ref)
{
	return (extract_material(ref));
}

/*
** object_normal_at() - BONUS VERSION
** Includes cone normal calculation
*/
t_tuple	object_normal_at(t_object_ref ref, t_tuple world_point)
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

t_tuple	ambient_component(t_world world, t_comps *comps)
{
	double	coeff;
	t_tuple	color;

	if (world.ambient_ratio <= 0.0)
		return (color_d(0, 0, 0));
	coeff = comps->material.ambient * world.ambient_ratio;
	color = multiply_tuples(comps->material.color, world.ambient_color);
	return (multiply_tuple_scalar(color, coeff));
}

t_lighting_args	build_light_args(t_world world, t_comps *comps, int index)
{
	t_lighting_args	args;
	t_material		material_copy;

	material_copy = comps->material;
	material_copy.ambient = 0.0;
	args.material = material_copy;
	args.light = world.lights[index];
	args.position = comps->over_point;
	args.eyev = comps->eyev;
	args.normalv = comps->normalv;
	args.in_shadow = is_shadowed_from_light(world,
			comps->over_point, world.lights[index]);
	return (args);
}


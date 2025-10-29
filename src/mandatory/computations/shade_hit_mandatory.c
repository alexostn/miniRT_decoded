/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit_mandatory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:23:53 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/29 19:13:38 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computations.h"
#include "world.h"
#include "materials.h"
#include "lights.h"
#include "computations_object_lookup.h"

/*
** shade_hit() - MANDATORY VERSION
** Uses only the single world.light (not the lights[] array)
*/
t_tuple	shade_hit(t_world world, t_comps comps)
{
	t_lighting_args	args;
	t_tuple			color;
	t_material		material_copy;

	color = ambient_component(world, &comps);
	if (!world.light_present)
		return (color);
	material_copy = comps.material;
	material_copy.ambient = 0.0;
	args.material = material_copy;
	args.light = world.light;
	args.position = comps.over_point;
	args.eyev = comps.eyev;
	args.normalv = comps.normalv;
	args.in_shadow = is_shadowed_from_light(world,
			comps.over_point, world.light);
	color = add(color, lighting(args));
	return (color);
}

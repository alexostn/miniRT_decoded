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
/*
** prepare_computations()
** Precompute useful data for shading an intersection
**
** Parameters:
** - i: intersection structure (t_intersection)
** - r: ray along which the intersection occurred (t_ray)
**
** Returns:
** - t_comps: structure with precomputed values (t, object, point, eyev, normalv)
*/
t_comps	prepare_computations_sphere(t_intersection i, t_ray r, t_sphere s)
{
	t_comps	comps;

	comps.t = i.t;
	comps.sphere = s;
	comps.point = ray_position(r, comps.t);
	comps.eyev = multiply_tuple_scalar(r.direction, -1);
	comps.normalv = sphere_normal_at(&comps.sphere, comps.point);
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside_hit = 1;
		comps.normalv = multiply_tuple_scalar(comps.normalv, -1);
	}
	else
		comps.inside_hit = 0;
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

	final_color = color_d(0, 0, 0);
	i = 0;
	while (i < world.lights_count)
	{
		args.material = comps.sphere.material;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:23:53 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:47:04 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computations.h"
#include "world.h"
#include "materials.h"
#include "computations_object_lookup.h"

/*
** shade_hit() - BONUS VERSION
** Supports multiple lights by iterating through world.lights[] array
*/
t_tuple	shade_hit(t_world world, t_comps comps)
{
	t_tuple	color;
	int		i;

	color = ambient_component(world, &comps);
	i = 0;
	while (i < world.lights_count)
	{
		color = add(color, lighting(build_light_args(world, &comps, i)));
		i++;
	}
	return (color);
}


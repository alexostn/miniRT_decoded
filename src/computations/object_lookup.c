/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_lookup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <unregistered>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 05:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/10/25 05:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "computations_object_lookup.h"

static t_object_ref	ref_make(void *ptr, t_object_type type)
{
	t_object_ref	ref;

	ref.ptr = ptr;
	ref.type = type;
	return (ref);
}

static t_object_ref	match_in_array(t_lookup_ctx ctx, void *ptr)
{
	int		index;
	char	*cursor;

	index = 0;
	cursor = (char *)ctx.array;
	while (index < ctx.count)
	{
		if ((void *)cursor == ptr)
			return (ref_make(ptr, ctx.type));
		cursor += ctx.stride;
		index++;
	}
	return (ref_make(NULL, OBJ_UNKNOWN));
}

t_object_ref	identify_object(t_world *world, void *ptr)
{
	t_lookup_ctx	ctxs[4];
	t_object_ref	ref;
	int				index;

	if (!world || !ptr)
		return (ref_make(NULL, OBJ_UNKNOWN));
	ctxs[0] = (t_lookup_ctx){world->spheres, sizeof(t_sphere),
		world->spheres_count, OBJ_SPHERE};
	ctxs[1] = (t_lookup_ctx){world->planes, sizeof(t_plane),
		world->planes_count, OBJ_PLANE};
	ctxs[2] = (t_lookup_ctx){world->cylinders, sizeof(t_cylinder),
		world->cylinders_count, OBJ_CYLINDER};
	ctxs[3] = (t_lookup_ctx){world->cones, sizeof(t_cone),
		world->cones_count, OBJ_CONE};
	index = 0;
	while (index < 4)
	{
		ref = match_in_array(ctxs[index], ptr);
		if (ref.type != OBJ_UNKNOWN)
			return (ref);
		index++;
	}
	return (ref_make(ptr, OBJ_UNKNOWN));
}

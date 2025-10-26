/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations_object_lookup.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:12:52 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/26 21:13:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTATIONS_OBJECT_LOOKUP_H
# define COMPUTATIONS_OBJECT_LOOKUP_H

# include "world.h"
# include "computations.h"

typedef struct s_lookup_ctx
{
	void		*array;
	size_t		stride;
	int		count;
	t_object_type	type;
}	t_lookup_ctx;

t_object_ref	identify_object(t_world *world, void *ptr);
t_material		extract_hit_material(t_object_ref ref);

t_tuple			object_normal_at(t_object_ref ref, t_tuple world_point);

t_tuple			ambient_component(t_world world, t_comps *comps);
t_lighting_args	build_light_args(t_world world, t_comps *comps, int index);

#endif

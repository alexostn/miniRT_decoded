/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:12:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/04 12:12:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_shape	shape_create(void)
{
	t_shape	sh;

	sh.transform = mat_identity();
	sh.material = material_create();
	return (sh);
}

t_shape	shape_set_transform(t_shape s, t_matrix m)
{
	s.transform = m;
	return (s);
}

t_shape	shape_set_material(t_shape s, t_material m)
{
	s.material = m;
	return (s);
}

t_ray	shape_transform_ray_to_local(t_shape *s, t_ray r)
{
	bool	 ok;
	t_matrix inv;

	inv = mat_inverse(s->transform, &ok);
	if (ok)
		r = ray_transform(r, inv);
	return (r);
}

t_tuple	shape_normal_at(t_shape *s, t_tuple world_point,
		t_tuple (*local_normal_at)(t_tuple local_point))
{
	bool	 ok;
	t_matrix inv;
	t_tuple	 local_point;
	t_tuple	 local_normal;
	t_tuple	 world_normal;

	inv = mat_inverse(s->transform, &ok);
	if (ok)
		local_point = mat_mul_tuple(inv, world_point);
	else
		local_point = world_point;
	local_normal = local_normal_at(local_point);
	inv = mat_inverse(s->transform, &ok);
	if (ok)
		world_normal = mat_mul_tuple(mat_transpose(inv), local_normal);
	else
		world_normal = local_normal;
	world_normal.w = 0.0;
	return (normalize_vector(world_normal));
}


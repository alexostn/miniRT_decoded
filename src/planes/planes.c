/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:17:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 21:53:56 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "planes.h"

t_plane	plane_create(void)
{
	t_plane	p;

	p.shape = shape_create();
	return (p);
}

t_tuple	plane_local_normal_at(t_tuple local_point)
{
	(void)local_point;
	return (vector(0, 1, 0));
}

t_plane	plane_set_transform(t_plane p, t_matrix transform)
{
	p.shape = shape_set_transform(p.shape, transform);
	return (p);
}

t_plane	plane_set_material(t_plane p, t_material material)
{
	p.shape = shape_set_material(p.shape, material);
	return (p);
}

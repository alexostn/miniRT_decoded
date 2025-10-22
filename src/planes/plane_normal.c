/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 22:04:32 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "planes.h"
#include "matrices.h"

t_tuple	plane_normal_at(t_plane *p, t_tuple world_point)
{
	return (shape_normal_at(&p->shape, world_point, plane_local_normal_at));
}

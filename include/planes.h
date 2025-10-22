/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:15:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 22:29:34 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANES_H
# define PLANES_H

# include "shapes.h"
# include "intersect.h"

/* Plane structure */
typedef struct s_plane
{
	t_shape	shape;
}	t_plane;

/* Plane creation and operations */
t_plane	plane_create(void);
t_plane	plane_set_transform(t_plane p, t_matrix transform);
t_plane	plane_set_material(t_plane p, t_material material);

/* Plane-specific local operations */
t_tuple	plane_local_normal_at(t_tuple local_point);
t_xs	plane_local_intersect(t_plane *p, t_ray local_ray);

/* Convenience: world-space intersect that transforms ray */
t_xs	plane_intersect(t_plane *p, t_ray r);

#endif

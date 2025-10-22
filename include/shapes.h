/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:10:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 16:26:07 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "matrices.h"
# include "materials.h"
# include "rays.h"
# include "tuples.h"

typedef struct s_shape
{
	t_matrix	transform;
	t_material	material;
}t_shape;

t_shape	shape_create(void);
t_shape	shape_set_transform(t_shape s, t_matrix m);
t_shape	shape_set_material(t_shape s, t_material m);

/* Utility helpers shared by concrete shapes/tests */
t_ray	shape_transform_ray_to_local(t_shape *s, t_ray r);
t_tuple	shape_normal_at(t_shape *s, t_tuple world_point,
		t_tuple (*local_normal_at)(t_tuple local_point));

#endif

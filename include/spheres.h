/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 22:31:13 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERES_H
# define SPHERES_H

# include "shapes.h"

/* Sphere structure - represents a unit sphere centered at origin */
typedef struct s_sphere
{
	t_matrix	transform;
	t_material	material;
}	t_sphere;

/* Sphere creation and operations */
t_sphere		sphere_create(void);
t_sphere		sphere_set_transform(t_sphere s, t_matrix transform);
t_sphere		sphere_set_material(t_sphere s, t_material material);
t_tuple			transform_point_to_object_space(t_sphere *s,
					t_tuple world_point);
t_tuple			sphere_normal_at(t_sphere *s, t_tuple world_point);

#endif

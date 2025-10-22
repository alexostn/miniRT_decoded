/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 16:58:25 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDERS_H
# define CYLINDERS_H

# include "shapes.h"
# include "intersect.h"

// Cylinder structure

typedef struct s_cylinder
{
	t_shape	shape;
	double	minimum;
	double	maximum;
	bool	closed;
}	t_cylinder;

// Cylinder creation and operations

t_cylinder	cylinder_create(void);

/* Local (object-space) operations */
t_xs		cylinder_local_intersect(t_cylinder *cyl, t_ray local_ray);
t_tuple		cylinder_local_normal_at(t_cylinder *cyl, t_tuple local_point);

/* World-space operations */
t_xs		cylinder_intersect(t_cylinder *cyl, t_ray r);
t_tuple		cylinder_normal_at(t_cylinder *cyl, t_tuple world_point);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:10:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 17:52:19 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONES_H
# define CONES_H

# include "shapes.h"
# include "intersect.h"

typedef struct s_cone
{
	t_shape	shape;
	double	minimum;
	double	maximum;
	bool	closed;
}	t_cone;

t_cone	cone_create(void);
t_xs	cone_local_intersect(t_cone *cone, t_ray local_ray);
t_tuple	cone_local_normal_at(t_cone *cone, t_tuple local_point);
t_xs	cone_intersect(t_cone *cone, t_ray r);
t_tuple	cone_normal_at(t_cone *cone, t_tuple world_point);

#endif

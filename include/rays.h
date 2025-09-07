/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/19 10:00:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "tuples.h"
# include "matrices.h"

/*
** Ray structure
** A ray has an origin (point) and a direction (vector)
** origin: starting point of the ray (w=1)
** direction: direction vector of the ray (w=0)
*/
typedef struct s_ray
{
	t_tuple	origin;		// point (w=1)
	t_tuple	direction;	// vector (w=0)
}	t_ray;

/*
** Ray constructors and operations
*/
t_ray	ray(t_tuple origin, t_tuple direction);
t_tuple	ray_position(t_ray r, double t);
t_ray	ray_transform(t_ray r, t_matrix m);

#endif

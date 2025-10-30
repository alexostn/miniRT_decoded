/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:06:22 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/26 17:03:27 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTILE_H
# define PROJECTILE_H

# include "tuples.h"
# include "environment.h"

typedef struct s_projectile
{
	t_tuple	position; // point (w=1)
	t_tuple	velocity; // vector (w=0)
}	t_projectile;

/// Creates a projectile (stack/heap)
t_projectile	projectile_create(t_tuple position, t_tuple velocity);

t_projectile	tick(t_environment env, t_projectile proj);

// Cleans up (relevant for heap)
// void			projectile_destroy(t_projectile *proj);

#endif
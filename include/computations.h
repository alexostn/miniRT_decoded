/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:37:39 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/07 17:28:11 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTATIONS_H
# define COMPUTATIONS_H

# include "tuples.h"
# include "spheres.h"
# include "rays.h"
# include "lighting.h"
# include "world.h"

typedef struct s_world	t_world;
/*
** Structure storing precomputed data about an intersection for shading
where t_sphere	sphere; is copy of sphere
*/
typedef struct s_comps
{
	double		t;
	t_sphere	sphere;
	t_tuple		point;
	t_tuple		over_point;
	t_tuple		eyev;
	t_tuple		normalv;
	bool		inside_hit;
}				t_comps;

t_comps	prepare_computations_sphere(t_intersection i, t_ray r, t_sphere s);
t_tuple	shade_hit(t_world world, t_comps comps);

#endif

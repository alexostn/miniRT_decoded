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
# include "rays.h"
# include "lighting.h"
# include "world.h"
# include "materials.h"
# include "intersect.h"

typedef struct s_world	t_world;

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_UNKNOWN
}	t_object_type;

typedef struct s_object_ref
{
	t_object_type	type;
	void			*ptr;
}	t_object_ref;

/*
** Structure storing precomputed data about an intersection for shading
*/
typedef struct s_comps
{
	double		t;
	t_object_ref	object;
	t_tuple		point;
	t_tuple		over_point;
	t_tuple		eyev;
	t_tuple		normalv;
	bool		inside_hit;
	t_material	material;
}				t_comps;

t_comps	prepare_computations(t_world *world, t_intersection hit, t_ray r);
t_tuple	shade_hit(t_world world, t_comps comps);

#endif

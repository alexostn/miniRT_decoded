/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 22:25:55 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include "matrices.h"
#include "materials.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*
** sphere_create()
** Creates a new unit sphere centered at origin with default material
**
** A unit sphere has radius 1 and is centered at (0,0,0). It starts with:
** - Identity transformation matrix (no scaling, rotation, or translation)
** - Default material (white, with realistic lighting properties)
**
** This is the basic building block for all spheres in the scene.
** Transformations and materials can be modified later using
** sphere_set_transform() and sphere_set_material().
**
** Returns:
** - t_sphere: new sphere with identity transformation and default material
*/
t_sphere	sphere_create(void)
{
	t_sphere	sphere;

	sphere.transform = mat_identity();
	sphere.material = material_create();
	return (sphere);
}

/*
** sphere_set_transform()
** Sets the transformation matrix for a sphere
**
** Transformations allow spheres to be scaled, rotated, and translated
** in 3D space. Common transformations include:
** - Scaling: making spheres larger or smaller
** - Translation: moving spheres to different positions
** - Rotation: orienting spheres in different directions
** - Combinations: applying multiple transformations
**
** The transformation matrix affects both the sphere's geometry and
** how normals are calculated for lighting.
**
** Parameters:
** - s: sphere to modify
** - transform: 4x4 transformation matrix to apply
**
** Returns:
** - t_sphere: sphere with new transformation applied
*/
t_sphere	sphere_set_transform(t_sphere s, t_matrix transform)
{
	s.transform = transform;
	return (s);
}

/*
** sphere_set_material()
** Sets the material properties for a sphere
**
** Materials define how a sphere interacts with light, including:
** - Color: the base color of the surface
** - Ambient: how much ambient light the surface reflects
** - Diffuse: how much directional light the surface scatters
** - Specular: how much light the surface reflects as highlights
** - Shininess: how focused the specular highlights are
**
** Different material combinations create different visual effects:
** - High diffuse, low specular: matte surfaces (paper, cloth)
** - Low diffuse, high specular: shiny surfaces (metal, glass)
** - High ambient: surfaces that glow or are self-illuminated
**
** Parameters:
** - s: sphere to modify
** - material: material properties to apply
**
** Returns:
** - t_sphere: sphere with new material properties
*/
t_sphere	sphere_set_material(t_sphere s, t_material material)
{
	s.material = material;
	return (s);
}

/*
** transform_point_to_object_space()
** Transforms a world point to object space using inverse transformation
**
** When a sphere has transformations (scaling, rotation, translation),
** we need to transform world coordinates back to the sphere's local
** object space to perform calculations like intersection testing.
**
** This is essential because:
** 1. Intersection algorithms work on unit spheres at origin
** 2. We need to "undo" transformations to work in object space
** 3. The inverse transformation matrix converts world → object coordinates
**
** For example, if a sphere is scaled by 2x and moved to (5,0,0):
** - World point (7,0,0) becomes object point (1,0,0)
** - This allows intersection testing on the unit sphere
**
** Parameters:
** - s: pointer to the sphere with transformation matrix
** - world_point: point in world coordinates
**
** Returns:
** - t_tuple: point in object space (sphere's local coordinates)
*/
t_tuple	transform_point_to_object_space(t_sphere *s,
				t_tuple world_point)
{
	t_tuple		object_point;
	t_matrix	inv_transform;
	bool		ok;

	if (!mat_equal(s->transform, mat_identity()))
	{
		inv_transform = mat_inverse(s->transform, &ok);
		if (ok)
			object_point = mat_mul_tuple(inv_transform, world_point);
		else
			object_point = world_point;
	}
	else
	{
		object_point = world_point;
	}
	return (object_point);
}

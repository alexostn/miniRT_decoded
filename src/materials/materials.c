/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:08:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/21 12:08:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "materials.h"
#include "colors.h"

/*
** material_create()
** Creates a default material with realistic lighting properties
**
** The default values are chosen to create a visually appealing material
** that behaves like a typical matte surface with some shine:
**
** - color (1,1,1): Pure white - shows the true color of light sources
** - ambient 0.1: 10% ambient lighting - prevents completely black shadows
** - diffuse 0.9: 90% diffuse lighting - most of the surface responds to light
** - specular 0.9: 90% specular reflection - creates visible highlights
** - shininess 200: High shininess - creates tight, focused highlights
**
** Returns:
** - t_material: material with default realistic properties
*/
t_material	material_create(void)
{
	t_material	material;

	material.color = color_d(1.0, 1.0, 1.0);
	material.ambient = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200.0;
	return (material);
}

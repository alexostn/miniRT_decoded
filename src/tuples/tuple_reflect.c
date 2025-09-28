/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_reflect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/21 12:00:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

/*
** reflect()
** Calculates the reflection of an incident vector off a surface
**
** Implements the reflection formula: R = I - 2(I·N)N
** where:
** - I is the incident vector (incoming direction)
** - N is the surface normal vector
** - R is the reflected vector (outgoing direction)
** - (I·N) is the dot product of incident and normal
**
** This is essential for calculating specular highlights in the Phong
** lighting model, where we need to know how light reflects off surfaces
** to determine if it reaches the viewer's eye.
**
** Parameters:
** - in: incident vector (direction of incoming light/ray)
** - normal: surface normal vector (must be normalized)
**
** Returns:
** - t_tuple: reflected vector (direction of reflected light/ray)
*/
t_tuple	reflect(t_tuple in, t_tuple normal)
{
	t_tuple	scaled;

	scaled = multiply_tuple_scalar(normal, 2.0 * dot_product(in, normal));
	return (substract_tuples(in, scaled));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:02:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 22:27:24 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinders.h"
#include "matrices.h"
#include "materials.h"
#include "defines.h"
#include <math.h>

t_cylinder	cylinder_create(void)
{
	t_cylinder	c;

	c.shape = shape_create();
	c.minimum = -INFINITY;
	c.maximum = INFINITY;
	c.closed = false;
	return (c);
}

t_cylinder	cylinder_set_transform(t_cylinder c, t_matrix transform)
{
	c.shape = shape_set_transform(c.shape, transform);
	return (c);
}

t_cylinder	cylinder_set_material(t_cylinder c, t_material material)
{
	c.shape = shape_set_material(c.shape, material);
	return (c);
}

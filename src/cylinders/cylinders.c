/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:02:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/22 15:57:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinders.h"
#include <math.h>
#include "defines.h"

t_cylinder	cylinder_create(void)
{
	t_cylinder	c;

	c.shape = shape_create();
	c.minimum = -INFINITY;
	c.maximum = INFINITY;
	c.closed = false;
	return (c);
}

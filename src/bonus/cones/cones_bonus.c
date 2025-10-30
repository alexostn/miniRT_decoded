/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:12:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/29 19:10:43 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones.h"
#include <math.h>
#include "defines.h"

t_cone	cone_create(void)
{
	t_cone	c;

	c.shape = shape_create();
	c.minimum = -INFINITY;
	c.maximum = INFINITY;
	c.closed = false;
	return (c);
}

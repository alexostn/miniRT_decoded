/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:11:14 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/27 16:26:11 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

// Creates a general tuple
t_tuple	tuple(double x, double y, double z, double w)
{
	t_tuple	new_tuple;

	new_tuple.x = x;
	new_tuple.y = y;
	new_tuple.z = z;
	new_tuple.w = w;
	return (new_tuple);
}

// Creates a point (w = 1.0)
t_tuple	point(double x, double y, double z)
{
	return (tuple(x, y, z, 1.0));
}

// Creates a vector (w = 0.0)
t_tuple	vector(double x, double y, double z)
{
	return (tuple(x, y, z, 0.0));
}

// Colors are vectors (w = 0.0)
// In code: color.x is r, color.y is g, color.z is b
t_tuple	color(double x, double y, double z)
{
	return (tuple(x, y, z, 0.0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_magitude_normalize_dot.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:13:14 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/17 00:42:57 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"
#include <math.h> // Make sure to include math.h for sqrt and pow

double	magnitude_of_vector(t_tuple v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_tuple	normalize_vector(t_tuple v)
{
	double	magnitude;
	t_tuple	normalized;

	magnitude = magnitude_of_vector(v);
	if (magnitude == 0) // Avoid division by zero
	{
		normalized.x = 0;
		normalized.y = 0;
		normalized.z = 0;
		normalized.w = 0;
		return (normalized);
	}
	normalized.x = v.x / magnitude;
	normalized.y = v.y / magnitude;
	normalized.z = v.z / magnitude;
	normalized.w = 0;
	return (normalized);
}

double	dot_product(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

t_tuple	cross_product(t_tuple a, t_tuple b)
{
	t_tuple	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	cross.w = 0.0;
	return (cross);
}
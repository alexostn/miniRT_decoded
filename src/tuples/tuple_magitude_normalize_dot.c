/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_magitude_normalize_dot.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:13:14 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/22 17:42:01 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

double	magnitude_of_vector(t_tuple v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

//NB: YOU CAN USE IT FOR POINTS/COLORS AS WELL THEY ARE TUPLES ALSO
t_tuple	normalize_vector(t_tuple v)
{
	double	magnitude;
	t_tuple	normalized;

	magnitude = magnitude_of_vector(v);
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

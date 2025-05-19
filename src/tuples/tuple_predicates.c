/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_predicates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:38:23 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/19 17:20:16 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

// Helper function for comparing doubles considering EPSILON
int	floats_equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}

// Checks if the tuple is a point
int	is_point(t_tuple t)
{
	return (floats_equal(t.w, 1.0));
}

// Checks if the tuple is a vector
int	is_vector(t_tuple t)
{
	return (floats_equal(t.w, 0.0));
}

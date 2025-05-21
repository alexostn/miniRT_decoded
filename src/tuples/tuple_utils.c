/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:41:31 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/21 19:34:05 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

// Compares two tuples for equality
// floats_equal is in tuple_predicates.c
// and is accessible via a header file

int	tuples_equal(t_tuple t1, t_tuple t2)
{
	if (floats_equal(t1.x, t2.x) && \
		floats_equal(t1.y, t2.y) && \
		floats_equal(t1.z, t2.z) && \
		floats_equal(t1.w, t2.w))
		return (1);
	return (0);
}

// Scenario: Adding two tuples
// Given a1 ← tuple(3, -2, 5, 1)
// And a2 ← tuple(-2, 3, 1, 0)
// Then a1 + a2 = tuple(1, 1, 6, 1)

t_tuple add_two_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple tsum;
	
	tsum.x = t1.x + t2.x;
	tsum.y = t1.y + t2.y;
	tsum.z = t1.z + t2.z;
	tsum.w = t1.w + t2.w;//TODO: can not 2 points
	
	return (tsum);
}

// Scenario: Subtracting two points
// Given p1 ← point(3, 2, 1)
// And p2 ← point(5, 6, 7)
// Then p1 - p2 = vector(-2, -4, -6)
// TODO: may be use is_point is_vector

t_tuple substract_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple tdiff;
	
	tdiff.x = t1.x - t2.x;
	tdiff.y = t1.y - t2.y;
	tdiff.z = t1.z - t2.z;
	tdiff.w = t1.w - t2.w;
	
	return (tdiff);
}

// Scenario: Subtracting a vector from a point
// Given p ← point(3, 2, 1)
// And v ← vector(5, 6, 7)
// Then p - v = point(-2, -4, -6)

// TO CHANGE DIRECTION BTW 2 VECTORS:
// Scenario: Subtracting two vectors
// Given v1 ← vector(3, 2, 1)
// And v2 ← vector(5, 6, 7)
// Then v1 - v2 = vector(-2, -4, -6)

//TODO: point (w = 1) from a vector (w = 0) = -1

// Scenario: Subtracting a vector from the zero vector
// Given zero ← vector(0, 0, 0)
// And v ← vector(1, -2, 3)
// Then zero - v = vector(-1, 2, -3)

t_tuple negate_tupil(t_tuple negatable)
{
	t_tuple zero = tuple(0, 0, 0, 0);

	return (substract_tuples(zero, negatable));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:41:31 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/19 18:06:52 by oostapen         ###   ########.fr       */
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
	tsum.w = t1.w + t2.w;
	
	return tsum;
}

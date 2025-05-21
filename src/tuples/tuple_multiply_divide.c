/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_multiply_divide.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:10:37 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/21 20:14:25 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

// BOTH ARE SIMILAR I DID THE FIRST ONLY:
// Scenario: Multiplying a tuple by a scalar
// Given a ← tuple(1, -2, 3, -4)
// Then a * 3.5 = tuple(3.5, -7, 10.5, -14)

// Scenario: Multiplying a tuple by a fraction
// Given a ← tuple(1, -2, 3, -4)
// Then a * 0.5 = tuple(0.5, -1, 1.5, -2)

t_tuple multiply_tuple_scalar(t_tuple a, double scalar)
{
	t_tuple tproduct;

	tproduct.x = a.x * scalar;
	tproduct.y = a.y * scalar;
	tproduct.z = a.z * scalar;
	tproduct.w = a.w * scalar;

	return (tproduct);
}

t_tuple divide_tuple_scalar(t_tuple d, double scalar)
{
	t_tuple	tquotient;

	tquotient.x = d.x / scalar;
	tquotient.y = d.y / scalar;
	tquotient.z = d.z / scalar;
	tquotient.w = d.w / scalar;

	return (tquotient);
}






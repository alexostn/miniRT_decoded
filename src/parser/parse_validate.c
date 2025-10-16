/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:32:59 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/17 00:43:19 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tuples.h"
#include "math_utils.h" // For floats_equal if you keep it, but range is better

bool	validate_range(double val, double min, double max)
{
	return (val >= min && val <= max);
}

/*
** Checks if a vector's magnitude is close to 1.
** Using a range is more robust than floats_equal due to precision errors.
*/
bool	validate_normalized(t_tuple vec)
{
	double	mag;

	mag = magnitude_of_vector(vec);
	// Instead of floats_equal(mag, 1.0), which is too strict:
	return (mag >= 0.99999 && mag <= 1.00001);
}

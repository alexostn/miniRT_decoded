/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:32:59 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/17 00:48:07 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tuples.h"

bool	validate_range(double val, double min, double max)
{
	return (val >= min && val <= max);
}

/*
** Checks if a vector's magnitude is close to 1.
** Using a range is more robust than direct comparison due to precision errors.
*/
bool	validate_normalized(t_tuple vec)
{
	double	mag;

	mag = magnitude_of_vector(vec);
	return (mag > (1.0 - EPS) && mag < (1.0 + EPS));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:32:59 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 22:33:01 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tuples.h"

bool	validate_range(double val, double min, double max)
{
	return (val >= min && val <= max);
}

bool	validate_normalized(t_tuple vec)
{
	double	magnitude;

	magnitude = magnitude_of_vector(vec);
	return (floats_equal(magnitude, 1.0));
}

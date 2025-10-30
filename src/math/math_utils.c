/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:06:04 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 15:23:42 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

/*
** Converts an angle from degrees to radians.
** Standard mathematical libraries use radians for trigonometric functions.
*/
double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double	radians_to_degrees(double radians)
{
	return (radians * 180.0 / M_PI);
}

double	clamp_double(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	approx_zero(double a)
{
	return (fabs(a) < EPS);
}

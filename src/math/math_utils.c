/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:06:04 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/13 22:57:51 by oostapen         ###   ########.fr       */
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

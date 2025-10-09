/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:04:48 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/09 21:57:58 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

//radians = degrees × (π / 180)
double	degrees_to_radians(double degrees);

//degrees = radians × (180 / π)
double	radians_to_degrees(double radians);

//clamps a double value between min and max
double	clamp_double(double value, double min, double max);

#endif

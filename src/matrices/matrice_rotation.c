/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:03:05 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/14 19:48:40 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformations.h"
#include <math.h>

/*
** @brief Creates a matrix to rotate a point around the X-axis.
** @param r The angle of rotation in radians.
** @return A t_matrix representing the rotation.
**
** The rotation matrix "X" is defined as (for left-handed coordinates):
**
**       x        y         z        w
**    ┌───────────────────────────────────┐
** x  | 1      0         0         0     |
** y  | 0    cos(r)    -sin(r)     0     |
** z  | 0    sin(r)     cos(r)     0     |
** w  | 0      0         0         1     |
**    └───────────────────────────────────┘
*/
t_matrix	rotation_x(double r)
{
	t_matrix	m;
	double		cos_r;
	double		sin_r;

	m = mat_identity();
	cos_r = cos(r);
	sin_r = sin(r);
	m.data[1][1] = cos_r;
	m.data[1][2] = -sin_r;
	m.data[2][1] = sin_r;
	m.data[2][2] = cos_r;
	return (m);
}

/*
** @brief Creates a matrix to rotate a point around the Y-axis.
** @param r The angle of rotation in radians.
** @return A t_matrix representing the rotation.
**
** The rotation matrix "Y" is defined as (for left-handed coordinates):
**
**       x       y        z         w
**    ┌───────────────────────────────────┐
** x  | cos(r)   0      sin(r)      0     |
** y  |   0      1        0         0     |
** z  | -sin(r)  0      cos(r)      0     |
** w  |   0      0        0         1     |
**    └───────────────────────────────────┘
*/
t_matrix	rotation_y(double r)
{
	t_matrix	m;
	double		cos_r;
	double		sin_r;

	m = mat_identity();
	cos_r = cos(r);
	sin_r = sin(r);
	m.data[0][0] = cos_r;
	m.data[0][2] = sin_r;
	m.data[2][0] = -sin_r;
	m.data[2][2] = cos_r;
	return (m);
}

/*
** @brief Creates a matrix to rotate a point around the Z-axis.
** @param r The angle of rotation in radians.
** @return A t_matrix representing the rotation.
**
** The rotation matrix "Z" is defined as (for left-handed coordinates):
**
**       x         y       z         w
**    ┌───────────────────────────────────┐
** x  | cos(r)   -sin(r)    0         0     |
** y  | sin(r)    cos(r)    0         0     |
** z  |   0         0       1         0     |
** w  |   0         0       0         1     |
**    └───────────────────────────────────┘
*/
t_matrix	rotation_z(double r)
{
	t_matrix	m;
	double		cos_r;
	double		sin_r;

	m = mat_identity();
	cos_r = cos(r);
	sin_r = sin(r);
	m.data[0][0] = cos_r;
	m.data[0][1] = -sin_r;
	m.data[1][0] = sin_r;
	m.data[1][1] = cos_r;
	return (m);
}

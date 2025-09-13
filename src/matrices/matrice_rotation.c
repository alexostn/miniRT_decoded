/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:03:05 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/13 23:27:38 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformations.h"

/*
** @brief Creates a matrix to rotate a point around the X-axis.
**
** This function generates a 4x4 transformation matrix that performs
** a rotation around the X-axis in a left-handed coordinate system.
**
** @param r The angle of rotation in radians.
** @return A t_matrix representing the rotation.
**
** The rotation matrix is defined as:
** | 1    0        0       0 |
** | 0  cos(r)  -sin(r)    0 |
** | 0  sin(r)   cos(r)    0 |
** | 0    0        0       1 |
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

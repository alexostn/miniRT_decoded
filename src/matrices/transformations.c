/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:02:25 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/16 22:05:20 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformations.h"

/*
** Creates a matrix to translate a point.
** x The distance to move along the X axis.
** y The distance to move along the Y axis.
** z The distance to move along the Z axis.
** A t_matrix representing the translation.
**
** The translation matrix is defined as:
**
**       x    y    z    w
**    ┌────────────────────┐
** x  |  1    0    0    x  |
** y  |  0    1    0    y  |
** z  |  0    0    1    z  |
** w  |  0    0    0    1  |
**    └────────────────────┘
*/
t_matrix	translation(double x, double y, double z)
{
	t_matrix	m;

	m = mat_identity();
	m.data[0][3] = x;
	m.data[1][3] = y;
	m.data[2][3] = z;
	return (m);
}

/*
** Creates a matrix to scale a point or vector.
**  x The scaling factor for the X axis.
**  y The scaling factor for the Y axis.
**  z The scaling factor for the Z axis.
**  A t_matrix representing the scaling operation.
**
** The scaling matrix is defined as:
**
**       x    y    z    w
**    ┌────────────────────┐
** x  |  x    0    0    0  |
** y  |  0    y    0    0  |
** z  |  0    0    z    0  |
** w  |  0    0    0    1  |
**    └────────────────────┘
*/
t_matrix	scaling(double x, double y, double z)
{
	t_matrix	m;

	m = mat_identity();
	m.data[0][0] = x;
	m.data[1][1] = y;
	m.data[2][2] = z;
	return (m);
}

/*
** Creates a shearing transformation matrix using parameters from a struct.
** The struct containing the six shearing parameters.
** A t_matrix representing the shearing transformation.
**
** The shearing matrix is defined as:
**
**       x    y    z    w
**    ┌────────────────────┐
** x  |  1   xy   xz   0   |
** y  | yx    1   yz   0   |
** z  | zx   zy    1   0   |
** w  |  0    0    0   1   |
**    └────────────────────┘
**
** Each parameter specifies how one coordinate is moved in proportion to another:
** - xy: how much x moves in proportion to y.
** - xz: how much x moves in proportion to z.
** - yx: how much y moves in proportion to x.
** - yz: how much y moves in proportion to z.
** - zx: how much z moves in proportion to x.
** - zy: how much z moves in proportion to y.
**
** Here we "feed" the coefficient 'xy' value:
** params = (t_shear_params){.xy = 1}; 
** All other fields in the struct are automatically set to zero.
*/
t_matrix	shearing(t_shear_params params)
{
	t_matrix	m;

	m = mat_identity();
	m.data[0][1] = params.xy;
	m.data[0][2] = params.xz;
	m.data[1][0] = params.yx;
	m.data[1][2] = params.yz;
	m.data[2][0] = params.zx;
	m.data[2][1] = params.zy;
	return (m);
}

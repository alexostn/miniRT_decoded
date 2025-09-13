/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:02:25 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/13 18:38:41 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformations.h"

/*
** Creates a translation matrix.
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
** Creates a scaling matrix.
** Takes the scaling factors for x, y, and z axes.
** Returns a 4x4 matrix that can be used to scale points and vectors.
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

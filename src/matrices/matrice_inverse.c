/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_inverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 22:19:45 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/10 18:50:53 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include <math.h> // For fabs()

// Helper function to create an identity matrix
static t_matrix	identity(void)
{
	t_matrix	id;
	int			row;
	int			col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			if (row == col)
				id.data[row][col] = 1.0;
			else
				id.data[row][col] = 0.0;
			col++;
		}
		row++;
	}
	return (id);
}

// Compute the inverse of a 4x4 matrix using cofactor expansion
// Sets *ok to true if successful, false if not invertible (det == 0)
// Returns the inverse if ok, otherwise returns identity matrix
// Transpose by assigning to inv.data[col][row]
// Divide cofactor by determinan
t_matrix	mat_inverse(t_matrix m, bool *ok)
{
	t_matrix	inv;
	double		det;
	int			row;
	int			col;

	row = 0;
	det = mat_determinant(m);
	if (det == 0.0)
	{
		*ok = false;
		return (identity());
	}
	*ok = true;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			inv.data[col][row] = mat_cofactor(m, row, col) / det;
			col++;
		}
		row++;
	}
	return (inv);
}

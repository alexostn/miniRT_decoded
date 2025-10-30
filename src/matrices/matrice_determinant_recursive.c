/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_determinant_recursive.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:36:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/11 20:23:34 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/*
** Recursive function to calculate the determinant of a matrix of a given size.
** This is the core of the determinant logic.
*/
double	mat_determinant_sized(t_matrix m, int size)
{
	double	det;
	int		col;

	if (size == 2)
		return (m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0]);
	det = 0.0;
	col = 0;
	while (col < size)
	{
		det += m.data[0][col] * mat_cofactor_sized(m, 0, col, size);
		col++;
	}
	return (det);
}

/*
** Calculates the cofactor of a matrix of a given size.
*/
double	mat_cofactor_sized(t_matrix m, int row, int col, int size)
{
	double	minor_val;

	minor_val = mat_minor_sized(m, row, col, size);
	if ((row + col) % 2 != 0)
		return (-minor_val);
	return (minor_val);
}

/*
** Calculates the minor of a matrix of a given size.
** The minor is the determinant of the submatrix.
*/
double	mat_minor_sized(t_matrix m, int row, int col, int size)
{
	return (mat_determinant_sized(mat_submatrix(m, row, col), size - 1));
}

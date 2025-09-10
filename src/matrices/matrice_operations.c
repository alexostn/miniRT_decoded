/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:54:32 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/10 19:04:23 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"
#include "matrices.h"
#include <stdbool.h>

bool	mat_equal(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (floats_equal(a.data[i][j], b.data[i][j]) == 0)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/*
*   mat_mul: Multiplies two 4x4 matrices.
*   For each cell in the result matrix, it computes the dot product of a row
*   from matrix 'a' and a column from matrix 'b'.
*
*   Parameters:
*   t_matrix a - The first matrix (left-hand side).
*   t_matrix b - The second matrix (right-hand side).
*
*   Returns:
*   A new t_matrix containing the product of a and b.
*/
t_matrix	mat_mul(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			row;
	int			col;
	double		dot_product;
	int			i;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			dot_product = 0.0;
			i = 0;
			while (i < 4)
			{
				dot_product += a.data[row][i] * b.data[i][col];
				i++;
			}
			result.data[row][col] = dot_product;
			col++;
		}
		row++;
	}
	return (result);
}

/**
 * @brief Multiplies a 4x4 matrix by a tuple (point or vector).
 *
 * This function performs the transformation of a tuple by a matrix.
 * Each component of the resulting tuple is the dot product of a matrix row
 * with the original tuple.
 *
 * @param m The 4x4 transformation matrix.
 * @param t The tuple (t_tuple) to be transformed.
 * @return The new, transformed tuple.
 */
t_tuple	mat_mul_tuple(t_matrix m, t_tuple t)
{
	t_tuple	result;

	result.x = m.data[0][0] * t.x + m.data[0][1] * t.y
		+ m.data[0][2] * t.z + m.data[0][3] * t.w;
	result.y = m.data[1][0] * t.x + m.data[1][1] * t.y
		+ m.data[1][2] * t.z + m.data[1][3] * t.w;
	result.z = m.data[2][0] * t.x + m.data[2][1] * t.y
		+ m.data[2][2] * t.z + m.data[2][3] * t.w;
	result.w = m.data[3][0] * t.x + m.data[3][1] * t.y
		+ m.data[3][2] * t.z + m.data[3][3] * t.w;
	return (result);
}

/*
* mat_transpose
*
* Description:
*   Creates and returns the transpose of a 4x4 matrix.
*   The transpose of a matrix is a new matrix whose rows are the columns of 
*   the original. (This is swapping the row and column indices.)
*
* Parameters:
*   t_matrix a - The matrix to be transposed.
*
* Returns:
*   t_matrix - The new transposed matrix.
*/
t_matrix	mat_transpose(t_matrix m)
{
	t_matrix	result;
	int			row;
	int			col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			result.data[row][col] = m.data[col][row];
			col++;
		}
		row++;
	}
	return (result);
}

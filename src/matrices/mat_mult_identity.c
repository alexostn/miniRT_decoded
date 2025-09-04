/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mult_identity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:01:38 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/05 00:12:43 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"   // Your header with t_tuple definition
#include "matrices.h" // Your header with t_matrix definition

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

/*
* Multiplies a 4x4 matrix by a tuple.
* This is used to apply transformations (scaling, rotation, translation)
* to points and vectors.
*/
// t_tuple	multiply_matrix_by_tuple(t_matrix m, t_tuple t)
// {
// 	t_tuple	result;

// 	result.x = m.m[0][0] * t.x + m.m[0][1] * t.y
// 		+ m.m[0][2] * t.z + m.m[0][3] * t.w;
// 	result.y = m.m[1][0] * t.x + m.m[1][1] * t.y
// 		+ m.m[1][2] * t.z + m.m[1][3] * t.w;
// 	result.z = m.m[2][0] * t.x + m.m[2][1] * t.y
// 		+ m.m[2][2] * t.z + m.m[2][3] * t.w;
// 	result.w = m.m[3][0] * t.x + m.m[3][1] * t.y
// 		+ m.m[3][2] * t.z + m.m[3][3] * t.w;
// 	return (result);
// }

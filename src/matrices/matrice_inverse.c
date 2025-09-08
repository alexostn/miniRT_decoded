/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_inverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 22:19:45 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/08 18:48:42 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include <math.h> // For fabs()

/*
** mat_inverse()
** Calculates the inverse of a 4x4 matrix.
**
** How it works:
** 1. Calculate the determinant. If it's zero, the matrix is not invertible.
** 2. For each element, calculate its cofactor.
** 3. Create a new matrix from these cofactors.
** 4. Transpose this new matrix (this gives the "adjugate" matrix).
** 5. Divide each element of the adjugate matrix by the original determinant.
**
** The pointer 'ok' is used to signal success or failure to the caller.
*/

// t_matrix	mat_inverse(t_matrix m, bool *ok)
// {
// 	t_matrix	inv;
// 	double		det;
// 	int			row;
// 	int			col;
// 	double		cofactor;

// 	// Step 1: Calculate determinant and check for invertibility
// 	det = mat_determinant(m);
// 	if (fabs(det) < EPS)
// 	{
// 		*ok = false;
// 		return (mat_identity()); // Return a default matrix
// 	}
// 	*ok = true;
// 	// Steps 2, 3, 4, and 5 combined
// 	row = 0;
// 	while (row < 4)
// 	{
// 		col = 0;
// 		while (col < 4)
// 		{
// 			// Calculate cofactor of element at (row, col)
// 			cofactor = mat_cofactor(m, row, col);
// 			// The "trick" is here: the cofactor of (row, col) goes into the
// 			// inverse matrix at position (col, row). This performs the
// 			// transposition of the cofactor matrix (the adjugate) and the
// 			// division by the determinant in one step.
// 			inv.data[col][row] = cofactor / det;
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (inv);
// }

// Helper function to create an identity matrix
static t_matrix identity(void)
{
    t_matrix id;
    int row = 0;
    int col;

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
    return id;
}
// Compute the inverse of a 4x4 matrix using cofactor expansion
// Sets *ok to true if successful, false if not invertible (det == 0)
// Returns the inverse if ok, otherwise returns identity matrix
t_matrix mat_inverse(t_matrix m, bool *ok)
{
    t_matrix inv;
    double det;
    int row = 0;
    int col;

    det = mat_determinant(m);
    if (det == 0.0)
    {
        *ok = false;
        return identity();
    }
    *ok = true;

    while (row < 4)
    {
        col = 0;
        while (col < 4)
        {
            // Transpose by assigning to inv.data[col][row]
            // Divide cofactor by determinant
            inv.data[col][row] = mat_cofactor(m, row, col) / det;
            col++;
        }
        row++;
    }
    return inv;
}



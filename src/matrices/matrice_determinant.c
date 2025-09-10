/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_determinant.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:06:48 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/10 20:48:18 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "libft.h"

// Determinant of 2x2 matrix (base case for recursion)
static double	mat_determinant_2x2(t_matrix m)
{
	return (m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0]);
}

// Determinant of 3x3 matrix (recursively calls cofactor, which calls 2x2)
static double	mat_determinant_3x3(t_matrix m)
{
	double	det;
	int		col;

	det = 0.0;
	col = 0;
	while (col < 3)
	{
		det += m.data[0][col] * mat_cofactor(m, 0, col);
		col++;
	}
	return (det);
}

double	mat_determinant(t_matrix m)
{
	double	det;
	int		col;

	det = 0.0;
	col = 0;
	while (col < 4)
	{
		det += m.data[0][col] * mat_cofactor(m, 0, col);
		col++;
	}
	return (det);
}

double	mat_minor(t_matrix m, int row, int col)
{
	t_matrix	sub;

	sub = mat_submatrix(m, row, col);
	if (sub.data[2][0] == 0 && sub.data[2][1] == 0 && sub.data[2][2] == 0 &&
			sub.data[0][2] == 0 && sub.data[1][2] == 0)
		return (mat_determinant_2x2(sub));
	return (mat_determinant_3x3(sub));
}

// Cofactor = minor * sign
double	mat_cofactor(t_matrix m, int row, int col)
{
	double	minor_val;

	minor_val = mat_minor(m, row, col);
	if ((row + col) % 2 != 0)
		return (-minor_val);
	return (minor_val);
}

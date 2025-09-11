/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:10:33 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/11 20:33:10 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

# include "tuples.h"
# include "defines.h"
# include <stdbool.h>

/*
** t_matrix: 4x4 matrix structure.
** Storage: Row-major layout -> data[row][col].
** Usage: Tuples are column vectors, multiplied on the right (M * t).
*/
typedef struct s_matrix
{
	double	data[4][4];
}	t_matrix;

/*
** -------------------------------------------------------------------------- **
**                               CORE OPERATIONS                              **
** -------------------------------------------------------------------------- **
*/

t_matrix	mat_identity(void);
t_matrix	mat_mul(t_matrix a, t_matrix b);
t_tuple		mat_mul_tuple(t_matrix m, t_tuple t);
t_matrix	mat_transpose(t_matrix m);
bool		mat_equal(t_matrix a, t_matrix b);

/*
** -------------------------------------------------------------------------- **
**                            INVERSION AND HELPERS                           **
** -------------------------------------------------------------------------- **
*/

t_matrix	mat_inverse(t_matrix m, bool *ok);
double		mat_determinant(t_matrix m);
double		mat_cofactor(t_matrix m, int row, int col);
double		mat_minor(t_matrix m, int row, int col);
t_matrix	mat_submatrix(t_matrix m, int row_to_skip, int col_to_skip);

// Internal recursive helpers
double		mat_determinant_sized(t_matrix m, int size);
double		mat_cofactor_sized(t_matrix m, int row, int col, int size);
double		mat_minor_sized(t_matrix m, int row, int col, int size);

/*
** -------------------------------------------------------------------------- **
**                          CONSTRUCTORS FOR TESTING                          **
** -------------------------------------------------------------------------- **
*/

t_matrix	create_matrix(double values[4][4]);
double		get_matrix_element(const t_matrix *m, int row, int col);

#endif

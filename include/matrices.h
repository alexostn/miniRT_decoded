/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:10:33 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/08 18:47:29 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

# include "tuples.h"
# include "defines.h"

/* bool in API prototypes */
# include <stdbool.h>

/* 
*	Storage/order:
*	- Row-major layout: data[row][col]
*	- Tuples are treated as column vectors on the right: result = M * t 
*/

typedef struct s_matrix
{
	double	data[4][4]; //- Row-major layout: data[row][col]
}	t_matrix;

t_matrix	mat_identity(void);
bool		mat_equal(t_matrix a, t_matrix b);
t_matrix	mat_mul(t_matrix a, t_matrix b);
t_tuple		mat_mul_tuple(t_matrix m, t_tuple t);
t_matrix	mat_transpose(t_matrix m);
double		mat_determinant(t_matrix m);
t_matrix	mat_inverse(t_matrix m, bool *ok);

// --- Determinant, Cofactor, and Inverse Functions are complex mechanism to be able to inverse ---

t_matrix	mat_submatrix(t_matrix m, int row_to_skip, int col_to_skip);
double		mat_determinant(t_matrix m);
double		mat_minor(t_matrix m, int row, int col);
double		mat_cofactor(t_matrix m, int row, int col);
t_matrix	mat_inverse(t_matrix m, bool *ok);

/* Constructors/accessors used by early tests */
t_matrix	create_matrix(double values[4][4]);
double		get_matrix_element(const t_matrix *m, int row, int col);

#endif

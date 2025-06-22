#ifndef MATRICES_H
# define MATRICES_H

// #include <assert.h>
// #include <stdio.h>

typedef struct s_matrix
{
	double data[4][4]; // [row][column]
} t_matrix;

t_matrix	create_matrix(double values[4][4]);
double	get_matrix_element(t_matrix *m, int row, int col);

#endif
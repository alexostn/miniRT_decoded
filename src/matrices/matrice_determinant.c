#include "matrices.h"
#include "libft.h"

// Determinant of 2x2 matrix (base case for recursion)
static double mat_determinant_2x2(t_matrix m) {
  return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
}

// Determinant of 3x3 matrix (recursively calls cofactor, which calls 2x2)
static double mat_determinant_3x3(t_matrix m) {
  double det = 0.0;
  int col = 0;
  while (col < 3) {
    det += m.data[0][col] * mat_cofactor(m, 0, col);
    col++;
  }
  return det;
}

// Determinant of 4x4 matrix (recursively calls cofactor, which calls 3x3)
double mat_determinant(t_matrix m) {
  double det = 0.0;
  int col = 0;
  while (col < 4) {
    det += m.data[0][col] * mat_cofactor(m, 0, col);
    col++;
  }
  return det;
}

// Submatrix (works for 4x4, copies into 3x3 for minor)
t_matrix mat_submatrix(t_matrix m, int row_to_skip, int col_to_skip) {
  t_matrix sub;
  int src_row = 0;
  int dst_row = 0;
  int src_col;
  int dst_col;
  ft_memset(sub.data, 0, sizeof(sub.data)); // Fill with zeros
  while (src_row < 4) {
    if (src_row == row_to_skip) {
      src_row++;
      continue;
    }
    dst_col = 0;
    src_col = 0;
    while (src_col < 4) {
      if (src_col == col_to_skip) {
        src_col++;
        continue;
      }
      sub.data[dst_row][dst_col] = m.data[src_row][src_col];
      dst_col++;
      src_col++;
    }
    dst_row++;
    src_row++;
  }
  return sub;
}

// // Minor = det of submatrix (recursively chooses det by size)
// double mat_minor(t_matrix m, int row, int col) {
//   t_matrix sub = mat_submatrix(m, row, col);
//   // Here we assume that for 3x3 sub is effectively 3x3, for 2x2 - 2x2.
//   // Since t_matrix is 4x4, but extra zeros are ignored in det_3x3/2x2.
//   return mat_determinant_3x3(sub); // For 4x4 minor - det 3x3. For tests 3x3 - det 3x3 will call det 2x2 inside.
// }

double mat_minor(t_matrix m, int row, int col)
{
	t_matrix sub = mat_submatrix(m, row, col);
	if (sub.data[2][0] == 0 && sub.data[2][1] == 0 && sub.data[2][2] == 0 &&
		sub.data[0][2] == 0 && sub.data[1][2] == 0) {
	return mat_determinant_2x2(sub);
	}
	return mat_determinant_3x3(sub);
}

// Cofactor = minor * sign
double mat_cofactor(t_matrix m, int row, int col)
{
	double minor_val = mat_minor(m, row, col);
	if ((row + col) % 2 != 0)
	{
	return -minor_val;
	}
	return minor_val;
}

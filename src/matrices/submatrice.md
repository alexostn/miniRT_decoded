/*NOT NECESSARY BUT GOOD FOR FUTURE SCALE METHOD:*/
typedef struct		s_matrix3
{
	double		data[3][3];
}			t_matrix3;

/*
** Function: submatrix
** ------------------
** Extracts 3x3 submatrix from 4x4 matrix by removing specified row and column.
** Used internally for computing minors, cofactors, determinants and inverse.
** 
** Parameters:
**   m   - input 4x4 matrix
**   row - row index to remove (0-based)
**   col - column index to remove (0-based)
**
** Returns: 3x3 matrix with specified row and column removed
**
** Note: Static function for internal use only within matrix module.
*/

static t_matrix3	submatrix(t_matrix m, int row, int col)
{
    t_matrix3	result;
    int			src_row;
    int			src_col;
    int			dst_row;
    int			dst_col;

    dst_row = 0;
    src_row = 0;
    while (src_row < 4)
    {
        if (src_row == row)
        {
            src_row++;
            continue;
        }
        dst_col = 0;
        src_col = 0;
        while (src_col < 4)
        {
            if (src_col != col)
            {
                result[dst_row][dst_col] = m[src_row][src_col];
                dst_col++;
            }
            src_col++;
        }
        dst_row++;
        src_row++;
    }
    return (result);
}


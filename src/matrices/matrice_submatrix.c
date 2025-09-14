/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_submatrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:47:48 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/10 20:48:48 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "libft.h"

static void	copy_row(double *dst_row, double *src_row, int col_to_skip)
{
	int	src_col;

	src_col = 0;
	while (src_col < 4)
	{
		if (src_col < col_to_skip)
			dst_row[src_col] = src_row[src_col];
		else if (src_col > col_to_skip)
			dst_row[src_col - 1] = src_row[src_col];
		src_col++;
	}
}

t_matrix	mat_submatrix(t_matrix m, int row_to_skip, int col_to_skip)
{
	t_matrix	sub;
	int			src_row;
	int			dst_row;

	src_row = 0;
	dst_row = 0;
	ft_memset(sub.data, 0, sizeof(sub.data));
	while (src_row < 4)
	{
		if (src_row == row_to_skip)
			src_row++;
		else
		{
			copy_row(sub.data[dst_row], m.data[src_row], col_to_skip);
			dst_row++;
			src_row++;
		}
	}
	return (sub);
}

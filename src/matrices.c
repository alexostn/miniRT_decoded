/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:34:24 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/04 16:34:35 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

t_matrix	create_matrix(double values[4][4])
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.data[i][j] = values[i][j];
			j++;
		}
		i++;
	}
	return (m);
}

// proceed mistake (return 0 or message)
double	get_matrix_element(const t_matrix *m, int row, int col)
{
	if (row < 0 || row >= 4 || col < 0 || col >= 4)
	{
		return (0.0);
	}
	return (m->data[row][col]);
}

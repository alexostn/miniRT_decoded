/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:34:24 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/04 23:56:08 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include <stdbool.h>

/* Build 4x4 identity: 1 on main diagonal, 0 elsewhere */
t_matrix	mat_identity(void)
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
			if (i == j)
				m.data[i][j] = 1.0;
			else
				m.data[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (m);
}

bool	mat_equal(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (floats_equal(a.data[i][j], b.data[i][j]) == 0)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

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

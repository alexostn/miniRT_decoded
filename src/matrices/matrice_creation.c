/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:38:08 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/05 19:42:08 by oostapen         ###   ########.fr       */
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

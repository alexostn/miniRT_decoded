/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:52:38 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/14 20:29:17 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "matrices.h"
# include "tuples.h"

// Structure for shearing parameters to comply with the Norm
typedef struct s_shear_params
{
	double	xy;
	double	xz;
	double	yx;
	double	yz;
	double	zx;
	double	zy;
}	t_shear_params;

// Function prototypes
t_matrix	translation(double x, double y, double z);
t_matrix	scaling(double x, double y, double z);
t_matrix	rotation_x(double r);
t_matrix	rotation_y(double r);
t_matrix	rotation_z(double r);
t_matrix	shearing(t_shear_params params);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cone_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 03:10:00 by alex              #+#    #+#             */
/*   Updated: 2025/10/27 03:10:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_cone.h"
#include "parser_utils.h"

bool	cone_build_transform(t_cone_input input, t_matrix *out)
{
	t_matrix	orient;
	t_matrix	scale;
	t_matrix	translate;
	t_tuple		axis_norm;

	axis_norm = normalize_vector(input.axis);
	if (!build_orientation_matrix(axis_norm, &orient))
		return (false);
	scale = scaling(input.diameter / 2.0, input.height,
			input.diameter / 2.0);
	translate = translation(input.center.x, input.center.y, input.center.z);
	*out = mat_mul(translate, mat_mul(orient, scale));
	return (true);
}

void	cone_apply_properties(t_cone *cone, t_cone_input input)
{
	cone->minimum = 0.0;
	cone->maximum = 1.0;
	cone->closed = true;
	cone->shape.material.color = input.color;
}

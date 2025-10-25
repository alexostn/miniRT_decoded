/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_orientation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <unregistered>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 05:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/10/25 05:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parser_utils.h"
#include "tuples.h"
#include "matrices.h"

static t_tuple	choose_reference_axis(t_tuple up)
{
	if (fabs(dot_product(up, vector(0, 1, 0))) > 0.999)
		return (vector(1, 0, 0));
	return (vector(0, 1, 0));
}

static bool	build_axes(t_tuple up, t_tuple *right, t_tuple *forward)
{
	t_tuple	reference;

	reference = choose_reference_axis(up);
	*right = cross_product(reference, up);
	if (magnitude_of_vector(*right) < EPS)
		return (false);
	*right = normalize_vector(*right);
	*forward = cross_product(up, *right);
	*forward = normalize_vector(*forward);
	return (true);
}

bool	build_orientation_matrix(t_tuple direction, t_matrix *out)
{
	t_tuple	up;
	t_tuple	right;
	t_tuple	forward;

	if (!out)
		return (false);
	up = normalize_vector(direction);
	if (magnitude_of_vector(up) < EPS)
		return (false);
	if (!build_axes(up, &right, &forward))
		return (false);
	*out = mat_identity();
	(*out).data[0][0] = right.x;
	(*out).data[0][1] = right.y;
	(*out).data[0][2] = right.z;
	(*out).data[1][0] = up.x;
	(*out).data[1][1] = up.y;
	(*out).data[1][2] = up.z;
	(*out).data[2][0] = forward.x;
	(*out).data[2][1] = forward.y;
	(*out).data[2][2] = forward.z;
	return (true);
}

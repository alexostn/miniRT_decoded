/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:41:31 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/03 22:30:13 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tuples.h" // t_tuple, prototypes, EPS via defines.h
# include <math.h> // fabs

/* --------------------------------------------------------------------------
** BEGIN: Added helper for robust float comparison (abs/rel tolerance)
** |a-b| <= max(absTol, relTol * max(|a|,|b|))
** Use for tricky tests with different scales or accumulated error.
** -------------------------------------------------------------------------- /
*/
int floats_close(double a, double b, double absTol, double relTol)
{
double diff = a - b;
if (diff < 0)
diff = -diff;
double aa = fabs(a);
double bb = fabs(b);
double maxab = (aa > bb) ? aa : bb;
double tol_rel = relTol * maxab;
double tol = (absTol > tol_rel) ? absTol : tol_rel;
return (diff <= tol);
}

// Compares two tuples for equality
// floats_equal is in tuple_predicates.c
// and is accessible via a header file

int	tuples_equal(t_tuple t1, t_tuple t2)
{
	if (floats_equal(t1.x, t2.x) && \
		floats_equal(t1.y, t2.y) && \
		floats_equal(t1.z, t2.z) && \
		floats_equal(t1.w, t2.w))
		return (1);
	return (0);
}

// tsum.w = t1.w + t2.w;//TODO: can not 2 points
t_tuple	add(t_tuple t1, t_tuple t2)
{
	t_tuple	tsum;

	tsum.x = t1.x + t2.x;
	tsum.y = t1.y + t2.y;
	tsum.z = t1.z + t2.z;
	tsum.w = t1.w + t2.w;
	return (tsum);
}

//TODO: point (w = 1) from a vector (w = 0) = -1 :
t_tuple	substract_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple	tdiff;

	tdiff.x = t1.x - t2.x;
	tdiff.y = t1.y - t2.y;
	tdiff.z = t1.z - t2.z;
	tdiff.w = t1.w - t2.w;
	return (tdiff);
}

t_tuple	negate_tupil(t_tuple negatable)
{
	t_tuple	zero;

	zero = tuple(0, 0, 0, 0);
	return (substract_tuples(zero, negatable));
}

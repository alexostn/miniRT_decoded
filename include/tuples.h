/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:47:48 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/20 13:19:47 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_H
# define TUPLES_H

# include <math.h> // for fabs
// If you have your own defines.h, EPSILON can be moved there
# ifndef EPSILON
#  define EPSILON 0.00001 // Precision for comparing float/double
# endif

// Structure for a tuple (can be a point or a vector)
// w = 1.0 for a point, w = 0.0 for a vector
typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

/*
** Functions to create tupils
** These functions return the structure by value (copying on the stack)
** For future heap usage: functions can be made that take a pointer to t_tuple
** for initialization (void tuple_init(t_tuple *dest, ...)) or return
** a pointer (t_tuple *tuple_create_heap(...))
*/
t_tuple	tuple(double x, double y, double z, double w);
t_tuple	point(double x, double y, double z);  // Constructor for a point
t_tuple	vector(double x, double y, double z); // Constructor for a vector

/*
** Predicate functions (checks)
*/
int		is_point(t_tuple t);
int		is_vector(t_tuple t);

/*
** Helper functions for comparison
*/
int		floats_equal(double a, double b);
int		tuples_equal(t_tuple t1, t_tuple t2);

/*** Tuple utils ***/

t_tuple add_two_tuples(t_tuple t1, t_tuple t2);
t_tuple substract_tuples(t_tuple t1, t_tuple t2);

/* Negate to change direction oposite for shadows */
t_tuple negate_tupil(t_tuple negatable);

/* Multiplying a tuple by a scalar/fraction */
t_tuple multiply_tuple_scalar(t_tuple a, double scalar);

#endif

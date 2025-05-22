/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_magitude_norm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:13:14 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/22 12:44:32 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

/*MAGNITUDE:*/

// Scenario: Computing the magnitude of vector(1, 0, 0)
// Given v ← vector(1, 0, 0)
// Then magnitude(v) = 1
// report erratum • discussOperations • 9

// Scenario: Computing the magnitude of vector(0, 1, 0)
// Given v ← vector(0, 1, 0)
// Then magnitude(v) = 1

// Scenario: Computing the magnitude of vector(0, 0, 1)
// Given v ← vector(0, 0, 1)
// Then magnitude(v) = 1

// Scenario: Computing the magnitude of vector(1, 2, 3)
// Given v ← vector(1, 2, 3)
// Then magnitude(v) = √14

// Scenario: Computing the magnitude of vector(-1, -2, -3)
// Given v ← vector(-1, -2, -3)
// Then magnitude(v) = √14

double	magnitude_of_vector(t_tuple v)
{
	double magnitude;
	
	magnitude = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	
	return (magnitude);
}
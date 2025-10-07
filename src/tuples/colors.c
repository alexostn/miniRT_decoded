/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:22:57 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/07 18:31:04 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

// for book tests where we receive data in range: 0 - 1
t_tuple	color_d(double r, double g, double b)
{
	return (tuple(r, g, b, 0.0));
}

// r -> x, g -> y, b -> z
t_tuple	rgb(double r, double g, double b)
{
	return (tuple(r, g, b, 0.0));
}

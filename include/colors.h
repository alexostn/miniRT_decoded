/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:49:28 by oostapen          #+#    #+#             */
/*   Updated: 2025/06/02 20:21:26 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "tuples.h"
// Means t_color = t_tuple
typedef t_tuple	t_color;

// Creates a color in the range 0.0–1.0 (for book tests)
t_tuple	color_d(double r, double g, double b);
// // TODO:
// // Converts color from 0–255 to 0.0–1.0 (for the project)
// t_tuple	color_c(double r, double g, double b);
// // TODO:
// // Scales color from 0.0–1.0 to 0–255 with clamping
// t_tuple	color_to_rgb255_scaled(double r_norm, double g_norm, double b_norm);

#endif

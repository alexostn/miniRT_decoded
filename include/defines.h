/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:11:17 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:03:48 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*for window not for FOV - small resolution for fast rendering (2.5x subject)*/
# define WIN_WIDTH 250
# define WIN_HEIGHT 125

/* precision for comparing float/double */
/*#  define EPS 1e-6 to be closer to book I came back to 0.00001 (1e-5)*/
# ifndef EPS
#  define EPS 0.00001
# endif
#endif

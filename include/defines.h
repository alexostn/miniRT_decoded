/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:11:17 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 19:12:33 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*for window not for FOV*/
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

/* precision for comparing float/double */
/*#  define EPS 1e-6 to be closer to book I came back to 0.00001 (1e-5)*/
# ifndef EPS
#  define EPS 0.00001
# endif
#endif

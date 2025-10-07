/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:22:50 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/07 22:56:35 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "tuples.h"
# include "matrices.h"

/*
[left.x    left.y    left.z    0]
[true_up.x true_up.y true_up.z 0]
[-fwd.x    -fwd.y    -fwd.z    0]
[0         0         0         1]
*/
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up);

#endif
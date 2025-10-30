/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:06:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/01 14:31:07 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "tuples.h"

typedef struct s_point_light
{
	t_tuple	position;
	t_tuple	intensity;
}	t_point_light;

t_point_light	point_light(t_tuple position, t_tuple intensity);

#endif

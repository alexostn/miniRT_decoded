/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:09:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/21 12:09:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

/*
** point_light()
** Creates a point light source with position and intensity
**
** Parameters:
** - position: 3D point where the light is located
** - intensity: color/brightness of the light (as RGB tuple)
**   For example, intensity (1,1,1) is white light, (1,0,0) is red light,
**   and (0.5,0.5,0.5) is dimmer white light.
** Returns:
** - t_point_light: light source structure with position and intensity
*/
t_point_light	point_light(t_tuple position, t_tuple intensity)
{
	t_point_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

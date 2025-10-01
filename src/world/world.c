/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:29:33 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/01 15:53:53 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
/* ----------------------- STACK VERSION UNDER ------------------------
** World construction: empty world
** - No light by default
** - No objects
** init light as absent or w.light.present = false
** init objects as absent or w.objects.ptr = NULL

t_world	world_make(void)
{
	t_world	w;

	w.light.present = false;
	w.spheres_count = 0;
	return (w);
}
*/
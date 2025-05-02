/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:10:41 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/03 00:35:55 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Initializes scene structure with default values
 * @param scene Pointer to scene structure to initialize
 */
void init_scene(t_scene *scene)
{
	scene->spheres = NULL;
	scene->sphere_count = 0;
	scene->planes = NULL;
	scene->plane_count = 0;
	scene->cylinders = NULL;
	scene->cylinder_count = 0;
}

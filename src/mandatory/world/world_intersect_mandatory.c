/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_intersect_mandatory.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:30:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/29 19:12:51 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "intersect.h"

static void	intersect_spheres(t_world *w, t_ray r, t_xs *result)
{
	t_xs	temp;
	int		i;

	i = -1;
	while (++i < w->spheres_count)
	{
		temp = sphere_intersect(&w->spheres[i], r);
		*result = intersections_add_all(*result, &temp);
		intersections_destroy(&temp);
	}
}

static void	intersect_planes(t_world *w, t_ray r, t_xs *result)
{
	t_xs	temp;
	int		i;

	i = -1;
	while (++i < w->planes_count)
	{
		temp = plane_intersect(&w->planes[i], r);
		*result = intersections_add_all(*result, &temp);
		intersections_destroy(&temp);
	}
}

static void	intersect_cylinders(t_world *w, t_ray r, t_xs *result)
{
	t_xs	temp;
	int		i;

	i = -1;
	while (++i < w->cylinders_count)
	{
		temp = cylinder_intersect(&w->cylinders[i], r);
		*result = intersections_add_all(*result, &temp);
		intersections_destroy(&temp);
	}
}

/*
** intersect_world() - MANDATORY VERSION
** Does NOT intersect with cones (bonus only)
*/
t_xs	intersect_world(t_world *w, t_ray r)
{
	t_xs	result;

	result = xs_create();
	intersect_spheres(w, r, &result);
	intersect_planes(w, r, &result);
	intersect_cylinders(w, r, &result);
	return (result);
}

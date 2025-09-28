/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_render_grid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/21 14:00:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"

static t_render_grid	grid_defaults(t_image *canvas)
{
	t_render_grid	grid;

	grid.origin = point(0, 0, -5);
	grid.wall_z = 10.0;
	grid.pixels = canvas->width;
	grid.pixel_size = 7.0 / grid.pixels;
	grid.half = 7.0 / 2.0;
	return (grid);
}

t_render_grid	render_grid_init(t_image *canvas)
{
	return (grid_defaults(canvas));
}

t_ray	render_grid_ray(t_render_grid *grid, int x, double world_y)
{
	t_tuple	position;
	t_tuple	direction;

	position = point(-grid->half + grid->pixel_size * x, world_y,
			grid->wall_z);
	direction = substract_tuples(position, grid->origin);
	return (ray(grid->origin, normalize_vector(direction)));
}

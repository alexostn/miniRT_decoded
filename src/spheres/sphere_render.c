/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/21 12:15:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_sphere.h"
#include "colors.h"

/*
** render_sphere_silhouette()
** Renders a sphere silhouette by casting rays from a fixed point
** to each pixel on a virtual wall behind the sphere
**
** Parameters:
** - canvas: pointer to the image canvas to draw on
** - sphere: the sphere to render
**
** Returns:
** - void
*/
static void	render_silhouette_row(t_render_job *job, int y)
{
	t_render_pixel	pixel;

	pixel.world_y = job->grid.half - job->grid.pixel_size * y;
	pixel.x = 0;
	while (pixel.x < job->grid.pixels)
	{
		pixel.ray = render_grid_ray(&job->grid, pixel.x, pixel.world_y);
		pixel.xs = sphere_intersect(job->sphere, pixel.ray);
		pixel.hit = intersections_hit(pixel.xs);
		if (pixel.hit.t >= 0)
			image_put_pixel(job->canvas, pixel.x, y, job->pixel_color);
		intersections_destroy(&pixel.xs);
		pixel.x++;
	}
}

static void	init_silhouette_job(t_render_job *job, t_image *canvas,
				t_sphere *sphere)
{
	t_color	color;

	job->canvas = canvas;
	job->sphere = sphere;
	job->grid = render_grid_init(canvas);
	color = (t_color){1.0, 0.0, 0.0, 1.0};
	job->pixel_color = color_to_mlx(&color, FORMAT_RGBA);
}

void	render_sphere_silhouette(t_image *canvas, t_sphere sphere)
{
	t_render_job	job;
	int				y;

	init_silhouette_job(&job, canvas, &sphere);
	y = 0;
	while (y < job.grid.pixels)
	{
		render_silhouette_row(&job, y);
		y++;
	}
}

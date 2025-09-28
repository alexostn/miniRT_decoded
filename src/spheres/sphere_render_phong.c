/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_render_phong.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/21 12:15:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include "image.h"
#include "colors.h"
#include "lights.h"
#include "lighting.h"

static void	put_phong_pixel(t_render_job *job, t_render_pixel *pixel, int y)
{
	t_sphere		*hit_sphere;
	t_lighting_args	args;
	t_color			color;

	hit_sphere = (t_sphere *)pixel->hit.object;
	args.material = hit_sphere->material;
	args.light = job->light;
	args.position = ray_position(pixel->ray, pixel->hit.t);
	args.eyev = negate_tupil(pixel->ray.direction);
	args.normalv = sphere_normal_at(hit_sphere, args.position);
	color = tuple_to_color(lighting(args));
	color.a = 1.0;
	image_put_pixel(job->canvas, pixel->x, y,
		color_to_mlx(&color, FORMAT_RGBA));
}

static void	render_phong_row(t_render_job *job, int y)
{
	t_render_pixel	pixel;

	pixel.world_y = job->grid.half - job->grid.pixel_size * y;
	pixel.x = 0;
	while (pixel.x < job->grid.pixels)
	{
		pixel.ray = render_grid_ray(&job->grid, pixel.x, pixel.world_y);
		pixel.xs = sphere_intersect(job->sphere, pixel.ray);
		pixel.hit = intersections_hit(pixel.xs);
		if (pixel.hit.object)
			put_phong_pixel(job, &pixel, y);
		intersections_destroy(&pixel.xs);
		pixel.x++;
	}
}

void	render_sphere_phong(t_image *canvas, t_sphere *sphere,
			t_point_light light)
{
	t_render_job	job;
	int				y;

	job.canvas = canvas;
	job.sphere = sphere;
	job.grid = render_grid_init(canvas);
	job.light = light;
	job.pixel_color = 0;
	y = 0;
	while (y < job.grid.pixels)
	{
		render_phong_row(&job, y);
		y++;
	}
}

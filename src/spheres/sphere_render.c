/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:00:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/09/20 17:20:39 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include "image.h"
#include "colors.h"
#include <math.h>
#include <stdio.h>

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

static t_silhouette_ctx	init_ctx(t_image *canvas)
{
	t_silhouette_ctx	ctx;
	t_color				color;

	ctx.origin = point(0, 0, -5);
	ctx.wall_z = 10.0;
	ctx.pixels = canvas->width;
	ctx.pixel_size = 7.0 / ctx.pixels;
	ctx.half = 7.0 / 2.0;
	color.r = 1.0;
	color.g = 0.0;
	color.b = 0.0;
	color.a = 1.0;
	ctx.pixel_color = color_to_mlx(&color, FORMAT_RGBA);
	return (ctx);
}

static t_ray	create_ray_for_pixel(t_silhouette_ctx *ctx,
		int x, double world_y)
{
	t_tuple	position;
	t_tuple	direction;

	position = point(-ctx->half + ctx->pixel_size * x, world_y, ctx->wall_z);
	direction = substract_tuples(position, ctx->origin);
	return (ray(ctx->origin, normalize_vector(direction)));
}

static void	render_row(t_image *canvas, t_sphere *sphere,
	t_silhouette_ctx *ctx, int y)
{
	t_xs			xs;
	t_intersection	hit;
	t_ray			ray;
	double			world_y;
	int				x;

	world_y = ctx->half - ctx->pixel_size * y;
	x = 0;
	while (x < ctx->pixels)
	{
		ray = create_ray_for_pixel(ctx, x, world_y);
		xs = sphere_intersect(sphere, ray);
		hit = intersections_hit(xs);
		if (hit.t >= 0)
			image_put_pixel(canvas, x, y, ctx->pixel_color);
		intersections_destroy(&xs);
		x++;
	}
}

void	render_sphere_silhouette(t_image *canvas, t_sphere sphere)
{
	t_silhouette_ctx	ctx;
	int					y;

	ctx = init_ctx(canvas);
	y = 0;
	while (y < ctx.pixels)
	{
		render_row(canvas, &sphere, &ctx, y);
		y++;
	}
}

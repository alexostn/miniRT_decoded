/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 20:12:22 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/09 22:11:49 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "camera.h"
#include "world.h"
#include "colors.h"

static void	render_pixel(t_image *image, t_camera *camera,
						t_world *world, t_pixel pixel)
{
	t_ray			ray;
	t_tuple			color_tuple;
	t_color_format	cf;

	ray = ray_for_pixel(camera, pixel.x, pixel.y);
	color_tuple = color_at(world, ray);
	cf.format = FORMAT_ARGB;
	cf.color = tuple_to_color(color_tuple);
	write_pixel(image, pixel.x, pixel.y, cf);
}

t_image	*render(void *mlx, t_camera camera, t_world *world)
{
	t_image	*image;
	t_pixel	pixel;

	image = image_create(mlx, camera.hsize, camera.vsize);
	if (!image)
		return (NULL);
	pixel.y = 0;
	while (pixel.y < camera.vsize)
	{
		pixel.x = 0;
		while (pixel.x < camera.hsize)
		{
			render_pixel(image, &camera, world, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	return (image);
}

/*
for DEBUG and see:
#include <stdio.h> //FOR PRINTF
// DEBUG: Print center pixel color BEFORE conversion
if (x == 5 && y == 5)
{
	printf("DEBUG: Center pixel color_tuple (before conversion):\n");
	printf("  r=%.5f g=%.5f b=%.5f\n",
		color_tuple.x, color_tuple.y, color_tuple.z);
}
// DEBUG END
*/
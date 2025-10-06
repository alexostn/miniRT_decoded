/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_demo_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 19:55:12 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/06 21:38:11 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "math_utils.h"
#include "world.h"
#include "computations.h"
#include "materials.h"
#include "transformations.h"
#include "matrices.h"
#include "lights.h"
#include "colors.h"

static void	ensure_dir(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		mkdir(path, 0775);
}

static void	world_add_sphere(t_world *world, t_sphere sphere)
{
	if (world->spheres_count >= MAX_OBJECTS)
		return ;
	world->spheres[world->spheres_count] = sphere;
	world->spheres_count++;
}

static t_matrix	wall_transform(double rotate_y)
{
	t_matrix	transform;

	transform = scaling(10, 0.01, 10);
	transform = mat_mul(rotation_x(M_PI / 2.0), transform);
	transform = mat_mul(rotation_y(rotate_y), transform);
	transform = mat_mul(translation(0, 0, 5), transform);
	return (transform);
}

static void	configure_shadow_scene(t_world *world)
{
	t_material	floor_material;
	t_sphere	sphere;
	t_material	material;

	*world = world_make();
	world->light_present = true;
	world->light = point_light(point(-10, 10, -10), color_d(1, 1, 1));
	floor_material = material_create();
	floor_material.color = color_d(1, 0.9, 0.9);
	floor_material.specular = 0.0;

	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, scaling(10, 0.01, 10));
	sphere = sphere_set_material(sphere, floor_material);
	world_add_sphere(world, sphere);

	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, wall_transform(-M_PI / 4.0));
	sphere = sphere_set_material(sphere, floor_material);
	world_add_sphere(world, sphere);

	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, wall_transform(M_PI / 4.0));
	sphere = sphere_set_material(sphere, floor_material);
	world_add_sphere(world, sphere);	

	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, translation(-0.5, 1.0, 0.5));
	material = sphere.material;
	material.color = color_d(0.1, 1.0, 0.5);
	material.diffuse = 0.7;
	material.specular = 0.3;
	sphere = sphere_set_material(sphere, material);
	world_add_sphere(world, sphere);

	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, mat_mul(translation(1.2, 0.5, -0.6),
			scaling(0.5, 0.5, 0.5)));
	material = sphere.material;
	material.color = color_d(0.5, 1.0, 0.1);
	material.diffuse = 0.7;
	material.specular = 0.3;
	sphere = sphere_set_material(sphere, material);
	world_add_sphere(world, sphere);

	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, mat_mul(translation(-1.5, 0.33, -0.75),
			scaling(0.33, 0.33, 0.33)));
	material = sphere.material;
	material.color = color_d(1.0, 0.8, 0.1);
	material.diffuse = 0.8;
	material.specular = 0.3;
	sphere = sphere_set_material(sphere, material);
	world_add_sphere(world, sphere);
}

static t_tuple	color_at_world(t_world *world, t_ray ray)
{
	t_xs			xs;
	t_intersection	hit;
	t_tuple		color;
	t_sphere		*object;
	t_comps		comps;

	xs = intersect_world(world, ray);
	hit = intersections_hit(xs);
	if (!hit.object)
	{
		intersections_destroy(&xs);
		return (color_d(0.0, 0.0, 0.0));
	}
	object = (t_sphere *)hit.object;
	comps = prepare_computations_sphere(hit, ray, *object);
	color = shade_hit(*world, comps);
	intersections_destroy(&xs);
	return (color);
}

static void	render_shadow_scene(void)
{
	t_world		world;
	t_render_grid	grid;
	int			x;
	int			y;
	int			fd;
	t_tuple		world_color;
	int			width;
	int			height;

	configure_shadow_scene(&world);
	width = 400;
	height = 400;
	fd = open("demos/output/shadow_scene.ppm",
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("   ✗ Failed to open output file\n");
		return ;
	}
	grid.origin = point(0, 1.5, -5);
	grid.wall_z = 0;
	grid.pixels = width;
	grid.half = 5.0;
	grid.pixel_size = (grid.half * 2.0) / (double)width;
	dprintf(fd, "P3\n%d %d\n255\n", width, height);
	y = 0;
	while (y < height)
	{
		double world_y;

		world_y = grid.half - grid.pixel_size * y;
		x = 0;
		while (x < width)
		{
			t_ray			ray;
			t_color		color;
			uint8_t		rgb[3];

			ray = render_grid_ray(&grid, x, world_y);
			world_color = color_at_world(&world, ray);
			color = tuple_to_color(world_color);
			rgb[0] = clamp_channel(color.r);
			rgb[1] = clamp_channel(color.g);
			rgb[2] = clamp_channel(color.b);
			dprintf(fd, "%d %d %d\n", rgb[0], rgb[1], rgb[2]);
			x++;
		}
		y++;
	}
	close(fd);
	printf("   ✓ Saved render to demos/output/shadow_scene.ppm\n");
}

int	main(void)
{
	printf("=== Shadow Casting Demo (Chapter 8) ===\n");
	printf("Rendering spheres with hard shadows...\n");
	ensure_dir("demos");
	ensure_dir("demos/output");
	render_shadow_scene();
	printf("\nDemo complete. Inspect demos/output/shadow_scene.ppm to view the result.\n");
	printf("Try experimenting with sphere transforms in shadow_demo_main.c to play with shadows!\n");
	return (0);
}

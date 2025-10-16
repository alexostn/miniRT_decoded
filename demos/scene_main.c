	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   chapter7_scene_main.c                              :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2025/10/11 21:00:00 by oostapen          #+#    #+#             */
	/*   Updated: 2025/10/12 17:38:02 by oostapen         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "demo_utils.h"
	#include "camera.h"
	#include "intersect.h"
	#include "lighting.h"

	// === BEGIN: LOCAL OVERRIDES FOR CHAPTER 7 (NO SHADOWS) ===

/*
** Local version of color_at() that calls lighting() directly,
** bypassing shade_hit() and is_shadowed().
*/
static t_tuple	color_at_no_shadow(t_world *world, t_ray ray)
{
	t_xs			xs;
	t_intersection	hit;
	t_comps			comps;
	t_tuple			color;
	t_sphere		*object;// Need a pointer to the sphere
	t_lighting_args	args;

	xs = intersect_world(world, ray);
	hit = intersections_hit(xs);
	if (!hit.object)
	{
		intersections_destroy(&xs);
		return (color_d(0, 0, 0));
	}
	object = (t_sphere *)hit.object;
	comps = prepare_computations_sphere(hit, ray, *object);

	args.material = object->material;
	args.light = world->light;
	args.position = comps.over_point;
	args.eyev = comps.eyev;
	args.normalv = comps.normalv;
	args.in_shadow = false;
	color = lighting(args);
	// color = lighting(object->material, world->light, comps.over_point,
	// 		comps.eyev, comps.normalv, false); // <-- in_shadow is always false
	intersections_destroy(&xs);
	return (color);
}

/*
** Local version of render() that uses our color_at_no_shadow().
*/
static t_image	*render_no_shadow(void *mlx, t_camera camera, t_world *world)
{
	t_image	*image;
	int		x;
	int		y;
	t_ray	ray;
	t_tuple			color_tuple;
	t_color			color;
	t_color_format	cf;

	image = image_create(mlx, camera.hsize, camera.vsize);
	if (!image)
		return (NULL);
	y = 0;
	while (y < camera.vsize)
	{
		x = 0;
		while (x < camera.hsize)
		{
			ray = ray_for_pixel(&camera, x, y);
			color_tuple = color_at_no_shadow(world, ray);
			color = tuple_to_color(color_tuple);
			cf.color = color;
			cf.format = FORMAT_ARGB;//or whatever format your MLX uses
			write_pixel(image, x, y, cf);
			x++;
		}
		y++;
	}
	return (image);
}

// === END: LOCAL OVERRIDES ===

/*
** world_add_sphere - Helper to add sphere to world (stack-based version)
** @world: Pointer to world structure
** @sphere: Sphere to add
**
** Description: Adds a sphere to the world's sphere array if there's space.
** This is a temporary stack-based helper. For heap-based version, replace
** with dynamic allocation logic (see docs/ARCHITECTURE.md).
*/
static void	world_add_sphere(t_world *world, t_sphere sphere)
{
	if (world->spheres_count >= MAX_OBJECTS)
		return ;
	world->spheres[world->spheres_count] = sphere;
	world->spheres_count++;
}

/*
** wall_transform - Compute transformation for a wall sphere
** @rotate_y: Y-axis rotation angle in radians
**
** Description: Creates a flattened sphere as a wall by applying:
** 1. Scale (10, 0.01, 10) - flatten to plane
** 2. Rotate X by π/2 - make it vertical
** 3. Rotate Y by rotate_y - orient left/right
** 4. Translate (0, 0, 5) - move to position
**
** Note: Order matters! Transformations are applied right-to-left.
*/
static t_matrix	wall_transform(double rotate_y)
{
	t_matrix	transform;

	/* Step 1: Scale to create flat plane */
	transform = scaling(10, 0.01, 10);
	
	/* Step 2: Rotate to make vertical */
	transform = mat_mul(rotation_x(M_PI / 2.0), transform);
	
	/* Step 3: Rotate around Y-axis for orientation */
	transform = mat_mul(rotation_y(rotate_y), transform);
	
	/* Step 4: Translate to final position */
	transform = mat_mul(translation(0, 0, 5), transform);

	return (transform);
}

/*
** configure_chapter7_scene - Set up the scene from "Putting It Together"
** @world: Pointer to world structure to configure
**
** Description: Creates the scene described in Chapter 7 "Putting It Together":
** - Floor: flattened sphere (10, 0.01, 10)
** - Left wall: rotated -45°
** - Right wall: rotated +45°
** - Middle sphere: green, at (-0.5, 1, 0.5)
** - Right sphere: smaller green, at (1.5, 0.5, -0.5)
** - Left sphere: smallest yellow, at (-1.5, 0.33, -0.75)
** - Light: point_light((-10, 10, -10), white)
**
** Note: This demonstrates proper transformation order and material setup
** from Chapter 7, page 106-107 of "The Ray Tracer Challenge".
*/
static void	configure_chapter7_scene(t_world *world)
{
	t_material	floor_material;
	t_sphere	sphere;
	t_material	material;

	/* === Initialize world === */
	*world = world_make();
	world->light_present = true;
	world->light = point_light(point(-10, 10, -10), color_d(1, 1, 1));

	/* === Configure floor material === */
	floor_material = material_create();
	floor_material.color = color_d(1, 0.9, 0.9);
	floor_material.specular = 0.0;

	/* === 1. Floor sphere === */
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, scaling(10, 0.01, 10));
	sphere = sphere_set_material(sphere, floor_material);
	world_add_sphere(world, sphere);

	/* === 2. Left wall (rotated -π/4) === */
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, wall_transform(-M_PI / 4.0));
	sphere = sphere_set_material(sphere, floor_material);
	world_add_sphere(world, sphere);

	/* === 3. Right wall (rotated +π/4) === */
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, wall_transform(M_PI / 4.0));
	sphere = sphere_set_material(sphere, floor_material);
	world_add_sphere(world, sphere);

	/* === 4. Middle sphere (large green) === */
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, translation(-0.5, 1.0, 0.5));
	material = sphere.material;
	material.color = color_d(0.1, 1.0, 0.5);
	material.diffuse = 0.7;
	material.specular = 0.3;
	sphere = sphere_set_material(sphere, material);
	world_add_sphere(world, sphere);

	/* === 5. Right sphere (medium green) === */
	/* Note: Transformations applied right-to-left: scale THEN translate */
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, 
		mat_mul(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5)));
	material = sphere.material;
	material.color = color_d(0.5, 1.0, 0.1);
	material.diffuse = 0.7;
	material.specular = 0.3;
	sphere = sphere_set_material(sphere, material);
	world_add_sphere(world, sphere);

	/* === 6. Left sphere (small yellow) === */
	/* Note: Scale by 0.33 BEFORE translating */
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, 
		mat_mul(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33)));
	material = sphere.material;
	material.color = color_d(1.0, 0.8, 0.1);
	material.diffuse = 0.7;
	material.specular = 0.3;
	sphere = sphere_set_material(sphere, material);
	world_add_sphere(world, sphere);
}

/*
** render_chapter7_scene_with_camera - Render using camera and render()
** @output_path: Path to save PPM file
**
** Description: Demonstrates the full rendering pipeline from Chapter 7:
** - camera_make() with FOV
** - view_transform() to position camera
** - render() function to generate image
**
** Camera setup from book (page 107):
**   camera(100, 50, π/3)
**   from: point(0, 1.5, -5)
**   to: point(0, 1, 0)
**   up: vector(0, 1, 0)
**
** Note: Using smaller resolution (100x50) as suggested in book:
** "stick with smaller resolutions while experimenting"
*/
static void	render_chapter7_scene_with_camera(const char *output_path)
{
	t_world		world;
	t_camera	camera;
	t_image		*image;
	void		*mlx;
	int			fd;

	/* === Initialize MLX === */
	mlx = mlx_init();
	if (!mlx)
	{
		printf("   ✗ Failed to initialize MLX\n");
		return ;
	}

	/* === Configure scene === */
	configure_chapter7_scene(&world);

	/* === Configure camera (from book page 107) === */
	camera = camera_make(100, 50, M_PI / 3.0);
	camera.transform = view_transform(
		point(0, 1.5, -5),   /* from */
		point(0, 0.5, 0),      /* to */
		vector(0, 1, 0)      /* up */
	);

	/* === Render scene === */
	printf("   → Rendering %dx%d image...\n", camera.hsize, camera.vsize);
	printf("   → Camera at (0, 1.5, -5) looking at (0, 1, 0)\n");
	printf("   → Scene contains %d objects\n", world.spheres_count);
	
	image = render_no_shadow(mlx, camera, &world);
	if (!image)
	{
		printf("   ✗ Failed to render image\n");
		return ;
	}

	/* === Save to PPM === */
	fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		image_to_ppm(image, fd);
		close(fd);
		printf("   ✓ Saved to %s\n", output_path);
		printf("   → Image demonstrates Chapter 7 concepts:\n");
		printf("     • World with multiple objects\n");
		printf("     • Camera with view_transform()\n");
		printf("     • Full render() pipeline\n");
		printf("     • Proper transformation order (scale → rotate → translate)\n");
	}
	else
		printf("   ✗ Failed to save to %s\n", output_path);

	image_destroy(image);
}

/*
** Main demo program for Chapter 7 "Putting It Together"
**
** - Complete rendering pipeline 
** (camera → ray_for_pixel → color_at → shade_hit)
**
** This scene has NO shadows (shadows are added in Chapter 8).
** Compare this output with shadow_demo_main.c to see the difference!
*/
int	main(void)
{
	printf("=== Chapter 7: Putting It Together ===\n");
	printf("Rendering the scene from 'The Ray Tracer Challenge' Ch7 pp.106-107\n\n");
	printf("Scene description:\n");
	printf("  • Floor: flattened sphere (10×0.01×10)\n");
	printf("  • 2 walls: rotated ±45°\n");
	printf("  • 3 spheres: large green, medium green, small yellow\n");
	printf("  • Light: point(-10, 10, -10)\n\n");

	ensure_demo_dirs();

	printf("Rendering with camera (100×50, FOV=π/3)...\n");
	render_chapter7_scene_with_camera("demos/output/chapter7_scene.ppm");

	printf("\n=== Demo Complete ===\n");
	printf("View: demos/output/chapter7_scene.ppm\n\n");
	printf("💡 Compare with Chapter 8 shadow demo:\n");
	printf("   Chapter 7 (no shadows): demos/output/chapter7_scene.ppm\n");
	printf("   Chapter 8 (with shadows): demos/output/shadow_scene.ppm\n\n");
	printf("📖 This demonstrates the scene from \"Putting It Together\" (Ch7)\n");
	printf("   before shadows are added in Chapter 8.\n");

	return (0);
}

#include "../test_common.h"

static void	assert_color_tuple_close(t_tuple color, double r, double g,
			double b, const char *message)
{
	bool	pass;

	pass = floats_close(color.x, r, EPS, EPS)
		&& floats_close(color.y, g, EPS, EPS)
		&& floats_close(color.z, b, EPS, EPS);
	TEST_ASSERT(pass, message);
}

static t_tuple	call_lighting_shadow(t_material material, t_point_light light,
			t_tuple position, t_tuple eyev, t_tuple normalv, bool in_shadow)
{
	t_lighting_args	args;

	args.material = material;
	args.light = light;
	args.position = position;
	args.eyev = eyev;
	args.normalv = normalv;
	args.in_shadow = in_shadow;
	return (lighting(args));
}

void	test_ch8_lighting_surface_in_shadow(void)
{
	t_material	material;
	t_tuple		position;
	t_tuple		result;

	printf("Chapter 8: Lighting with the surface in shadow\n");
	material = material_create();
	position = point(0, 0, 0);
	result = call_lighting_shadow(material,
		point_light(point(0, 0, -10), color_d(1, 1, 1)), position,
		vector(0, 0, -1), vector(0, 0, -1), true);
	assert_color_tuple_close(result, 0.1, 0.1, 0.1,
		"Lighting returns ambient when point shadowed");
}

void	test_ch8_is_shadowed_no_object_between(void)
{
	t_world	world;

	printf("Chapter 8: No shadow when nothing between point and light\n");
	world = default_world();
	TEST_ASSERT(is_shadowed(world, point(0, 10, 0)) == false,
		"is_shadowed returns false when path is clear");
}

void	test_ch8_is_shadowed_object_between_point_and_light(void)
{
	t_world	world;

	printf("Chapter 8: Shadow when object between point and light\n");
	world = default_world();
	TEST_ASSERT(is_shadowed(world, point(10, -10, 10)) == true,
		"is_shadowed returns true when object blocks light");
}

void	test_ch8_is_shadowed_object_behind_light(void)
{
	t_world	world;

	printf("Chapter 8: No shadow when object behind the light\n");
	world = default_world();
	TEST_ASSERT(is_shadowed(world, point(-20, 20, -20)) == false,
		"is_shadowed returns false when object behind light");
}

void	test_ch8_is_shadowed_object_behind_point(void)
{
	t_world	world;

	printf("Chapter 8: No shadow when object behind the point\n");
	world = default_world();
	TEST_ASSERT(is_shadowed(world, point(-2, 2, -2)) == false,
		"is_shadowed returns false when object behind point");
}

void	test_ch8_prepare_computations_offsets_point(void)
{
	t_ray			r;
	t_sphere		sphere;
	t_intersection	intersection;
	t_comps		comps;

	printf("Chapter 8: prepare_computations offsets the point\n");
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	sphere = sphere_create();
	sphere = sphere_set_transform(sphere, translation(0, 0, 1));
	intersection = intersection_create(5.0, &sphere);
	comps = prepare_computations_sphere(intersection, r, sphere);
	TEST_ASSERT(comps.over_point.z < -EPS / 2.0,
		"over_point.z is slightly less than zero");
	TEST_ASSERT(comps.point.z > comps.over_point.z,
		"over_point is above the surface point");
}

void	test_ch8_shade_hit_in_shadow(void)
{
	t_world		world;
	t_ray			r;
	t_intersection	intersection;
	t_comps		comps;
	t_tuple		color;

	printf("Chapter 8: shade_hit for intersection in shadow\n");
	world = world_make();
	world.light_present = true;
	world.light = point_light(point(0, 0, -10), color_d(1, 1, 1));
	world.spheres[0] = sphere_create();
	world.spheres_count = 1;
	world.spheres[1] = sphere_create();
	world.spheres[1] = sphere_set_transform(world.spheres[1],
		translation(0, 0, 10));
	world.spheres_count++;
	r = ray(point(0, 0, 5), vector(0, 0, 1));
	intersection = intersection_create(4.0, &world.spheres[1]);
	comps = prepare_computations_sphere(intersection, r, world.spheres[1]);
	color = shade_hit(world, comps);
	assert_color_tuple_close(color, 0.1, 0.1, 0.1,
		"shade_hit returns ambient when shadowed");
}

void	run_chapter8_tests(void)
{
	printf("\n=== Chapter 8: Shadows ===\n");
	test_ch8_lighting_surface_in_shadow();
	test_ch8_is_shadowed_no_object_between();
	test_ch8_is_shadowed_object_between_point_and_light();
	test_ch8_is_shadowed_object_behind_light();
	test_ch8_is_shadowed_object_behind_point();
	test_ch8_prepare_computations_offsets_point();
	test_ch8_shade_hit_in_shadow();
	printf("\n=== Chapter 8 Tests Complete ===\n\n");
}


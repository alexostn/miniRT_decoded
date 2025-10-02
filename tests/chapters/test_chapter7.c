#include "../test_common.h"

// TEST FUNCTIONS ONLY
void	test_ch7_creating_world(void)
{
	printf("Chapter 7: Creating a world\n\n");
	t_world w;

	w = world_make();
	printf("w.spheres_count = %d\n", w.spheres_count);
	print_light(&w.light, "Actual Light");
	TEST_ASSERT(w.spheres_count == 0, "world contains no objects");
}

/*
Scenario: The default world
Given light ← point_light(point(-10, 10, -10), color(1, 1, 1))
And s1 ← sphere() with:
| material.color
| (0.8, 1.0, 0.6)
|
| material.diffuse
| 0.7
|
| material.specular | 0.2
|
And s2 ← sphere() with:
| transform | scaling(0.5, 0.5, 0.5) |
When w ← default_world()
Then w.light = light
And w contains s1
And w contains s2
*/
void	test_ch7_default_world(void)
{
	printf("Chapter 7: The default world\n\n");
	t_world			w;
	t_point_light	expected_light;
	t_sphere		s1;
	t_sphere		s2;
	t_material		m1;

	// Create default world
	w = default_world();

	// Set up expected light
	expected_light = point_light(point(-10, 10, -10), point(1, 1, 1));

	// Set up expected first sphere
	s1 = sphere_create();
	m1 = material_create();
	m1.color = point(0.8, 1.0, 0.6);
	m1.diffuse = 0.7;
	m1.specular = 0.2;
	s1.material = m1;

	// Set up expected second sphere
	s2 = sphere_create();
	s2.transform = scaling(0.5, 0.5, 0.5);

	// Test light
	TEST_ASSERT(w.light_present, "Default world should have a light");
	TEST_ASSERT(tuples_equal(w.light.position, expected_light.position),
				"Light position is correct");
	TEST_ASSERT(tuples_equal(w.light.intensity, expected_light.intensity),
				"Light intensity is correct");

	// Test sphere count
	TEST_ASSERT(w.spheres_count == 2, "Default world contains 2 spheres");

	// Test first sphere
	TEST_ASSERT(spheres_equal(w.spheres[0], s1),
				"Default world contains s1");
	print_sphere("Actual s1", w.spheres[0]);
	print_sphere("s1", s1);

	// Test second sphere
	TEST_ASSERT(spheres_equal(w.spheres[1], s2),
				"Default world contains s2");
	print_sphere("Actual s2", w.spheres[1]);
	printf("\n");
}

/*
Scenario: Intersect a world with a ray
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 0, 1))
When xs ← intersect_world(w, r)Then xs.count = 4
And xs[0].t = 4
And xs[1].t = 4.5
And xs[2].t = 5.5
And xs[3].t = 6
*/
void	test_ch7_intersect_world_stack(void)
{
	t_world		w;
	t_ray		r;
	t_xs_stack	xs;

	printf("Chapter 7: Intersecting a world with a ray (STACK version)\n\n");
	
	/* START: Setup default world and ray */
	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	/* END: Setup default world and ray */
	
	/* START: Display world configuration */
	printf("World configuration:\n");
	printf("  Number of spheres: %d\n", w.spheres_count);
	printf("  Ray origin: (0, 0, -5)\n");
	printf("  Ray direction: (0, 0, 1)\n");
	printf("\n");
	/* END: Display world configuration */
	
	/* START: Perform intersection */
	xs = intersect_world_stack(&w, r);
	/* END: Perform intersection */
	
	/* START: Display results */
	printf("Intersection results:\n");
	printf("  Total intersections: %d\n", xs.count);
	printf("\n");
	
	if (xs.count >= 4)
	{
		printf("  xs[0].t = %.1f\n", xs.intersections[0].t);
		printf("  xs[1].t = %.1f\n", xs.intersections[1].t);
		printf("  xs[2].t = %.1f\n", xs.intersections[2].t);
		printf("  xs[3].t = %.1f\n", xs.intersections[3].t);
	}
	printf("\n");
	/* END: Display results */
	
	/* START: Assertions */
	TEST_ASSERT(xs.count == 4,
		"world intersection count is 4");
	TEST_ASSERT(fabs(xs.intersections[0].t - 4.0) < EPS,
		"xs[0].t = 4");
	TEST_ASSERT(fabs(xs.intersections[1].t - 4.5) < EPS,
		"xs[1].t = 4.5");
	TEST_ASSERT(fabs(xs.intersections[2].t - 5.5) < EPS,
		"xs[2].t = 5.5");
	TEST_ASSERT(fabs(xs.intersections[3].t - 6.0) < EPS,
		"xs[3].t = 6");
	/* END: Assertions */
}


void run_chapter7_tests(void)
{
	printf("\n=== Chapter 7: Making a Scene ===\n");
	test_ch7_creating_world();
	test_ch7_default_world();
	test_ch7_intersect_world_stack();
	printf("\n=== Chapter 7 Tests Complete ===\n\n");
}

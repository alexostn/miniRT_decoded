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
void	test_ch7_intersect_world(void)
{
	t_world	w;
	t_ray	r;
	t_xs	xs;

	printf("Chapter 7: Intersecting a world with a ray\n\n");
	
	/* Setup default world and ray */
	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 0, 1));

	/* Display world configuration */
	printf("World configuration:\n");
	printf("  Number of spheres: %d\n", w.spheres_count);
	print_ray(r);
	printf("\n");

	/* Perform intersection */
	xs = intersect_world(&w, r);

	/* Display results */
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
	
	/* Assertions */
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
}

/*
** test_ch7_prepare_computations()
** Checks that prepare_computations_sphere() correctly computes
** the intersection point, eye vector, and normal for a sphere.
*/
void test_ch7_prepare_computations(void)
{
	t_ray           r;
	t_sphere        s;
	t_intersection  i;
	t_comps         comps;

	printf("\n\nTest: Precomputing the state of an intersection (sphere)\n");
	/* Setup ray and sphere */
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere_create();

	/* Create intersection */
	i = intersection_create(4, NULL); // object not needed as sphere is inside comps

	/* Call the computation preparation function */
	comps = prepare_computations_sphere(i, r, s);

	/* Check results */
	TEST_ASSERT(fabs(comps.t - i.t) < EPS, "t matches intersection distance");
	/* other objects will come later */

	TEST_ASSERT(tuples_equal(comps.point, point(0, 0, -1)), "\n point of intersection is correct:");
	print_tuple(comps.point);
	TEST_ASSERT(tuples_equal(comps.eyev, vector(0, 0, -1)), "\n eye vector points to camera:");
	print_tuple(comps.eyev);
	TEST_ASSERT(tuples_equal(comps.normalv, vector(0, 0, -1)), "\n normal vector is correct:");
	print_tuple(comps.normalv);
}

void test_ch7_shade_hit_outside(void)
{
	printf("\n Test: Shade hit outside the sphere\n");
    t_world w = default_world();
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere *shape = &w.spheres[0];
    t_intersection i = intersection_create(4, shape);
    t_comps comps = prepare_computations_sphere(i, r, *shape);
    t_tuple c = shade_hit(w, comps);
	printf("outcome:\n");
    print_tuple(c);
    t_tuple expected = color_d(0.38066, 0.47583, 0.2855);
    print_tuple(expected);
    TEST_ASSERT(tuples_equal(c, expected), "shade_hit outside object returns correct color");
}

void test_ch7_shade_hit_inside(void)
{
	printf("\n Test: Shade hit inside the sphere\n");
	t_world w = default_world();

    /* Modify light position */
    w.light = point_light(point(0, 0.25, 0), color_d(1, 1, 1));

    t_ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    t_sphere *shape = &w.spheres[1];
    t_intersection i = intersection_create(0.5, shape);
    t_comps comps = prepare_computations_sphere(i, r, *shape);
    t_tuple c = shade_hit(w, comps);
	printf("outcome:\n");
    print_tuple(c);
    t_tuple expected = color_d(0.90498, 0.90498, 0.90498);
    print_tuple(expected);
    TEST_ASSERT(tuples_equal(c, expected), "shade_hit inside object returns correct color");
}


void run_chapter7_tests(void)
{
	printf("\n=== Chapter 7: Making a Scene ===\n");
	test_ch7_creating_world();
	test_ch7_default_world();
	test_ch7_intersect_world();
	test_ch7_prepare_computations();
	test_ch7_shade_hit_outside();
	test_ch7_shade_hit_inside();

	printf("\n=== Chapter 7 Tests Complete ===\n\n");
}

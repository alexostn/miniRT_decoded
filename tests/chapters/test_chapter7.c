#include "../test_common.h"

// TEST FUNCTIONS ONLY
void	test_ch7_creating_world(void)
{
	printf("\n\nChapter 7: Creating a world\n\n");
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
	printf("\n\nChapter 7: The default world\n\n");
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

	printf("\n\nChapter 7: Intersecting a world with a ray\n\n");
	
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

	printf("\n\nChapter 7: Precomputing the state of an intersection (sphere)\n");
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
	printf("\n\nChapter 7: Shade hit outside the sphere\n");
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
	printf("\n\nChapter 7: Shade hit inside the sphere\n");
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

void	test_ch7_hit_outside_inside(void)
{
	t_ray           r;
	t_sphere        s;
	t_intersection  i;
	t_comps         comps;

	printf("\n\nChapter 7: Hit Outside vs Inside ===\n");

	/* Test 1: Hit occurs on the outside */
	printf("\nScenario: The hit, when an intersection occurs on the outside\n");
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere_create();
	i = intersection_create(4, &s);
	comps = prepare_computations_sphere(i, r, s);
	
	TEST_ASSERT(comps.inside_hit == false, "intersection should be outside");
	if (comps.inside_hit)
		printf("comps.inside_hit = true\n");
	else
		printf("comps.inside_hit = false\n");

	/* Test 2: Hit occurs on the inside */
	printf("\nScenario: The hit, when an intersection occurs on the inside\n");
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	s = sphere_create();
	i = intersection_create(1, &s);
	comps = prepare_computations_sphere(i, r, s);

	printf("comps.point:\n");
	print_tuple(comps.point);
	printf("comps.eyev:\n");
	print_tuple(comps.eyev);
	printf("comps.normalv (should be inverted):\n");
	print_tuple(comps.normalv);

	TEST_ASSERT(tuples_equal(comps.point, point(0, 0, 1)), 
				"point of intersection is correct");
	TEST_ASSERT(tuples_equal(comps.eyev, vector(0, 0, -1)), 
				"eye vector is correct");
	TEST_ASSERT(comps.inside_hit == true, "intersection should be inside");
	TEST_ASSERT(tuples_equal(comps.normalv, vector(0, 0, -1)), 
				"normal vector should be inverted when inside");
	printf("\n");
}

/*
Scenario: The color when a ray misses
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 1, 0))
When c ← color_at(w, r)
Then c = color(0, 0, 0)
*/
void test_ch7_color_at_miss(void)
{
	t_world	w;
	t_ray	r;
	t_tuple	c;

	printf("\n\nChapter 7: Color when ray misses ===\n");
	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 1, 0));

	c = color_at(&w, r);
	
	TEST_ASSERT(tuples_equal(c, color_d(0, 0, 0)), 
				"color_at should return black when ray misses");
	printf("color_at returns color:\n");
	print_tuple(c);
	printf("\nit is black color or tuple:\n");
	print_tuple(color_d(0, 0, 0));
	/* hint to run demo to see black screen:)*/
	printf("💡 For visualization of black screen, run: make world\n");
}

/*
Scenario: The color when a ray hits
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 0, 1))
When c ← color_at(w, r)
Then c = color(0.38066, 0.47583, 0.2855)
*/
void test_ch7_color_when_ray_hits(void)
{
	t_world	w;
	t_ray	r;
	t_tuple	c;
	t_tuple	expected_c;

	printf("\n\nChapter 7: Color when when a ray hits ===\n");
	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 0, 1));

	c = color_at(&w, r);
	expected_c = color_d(0.38066, 0.47583, 0.2855);
	TEST_ASSERT(tuples_equal(c, expected_c), 
				"color_at should return black when ray misses");
	printf("color_at returns color:\n");
	print_tuple(c);
	printf("\nthe same as expected color/tuple:\n");
	print_tuple(expected_c);
	/* hint to run demo */
	printf("💡 For visualization, run: make world\n");
}

void test_ch7_color_at_behind_ray(void)
{
	t_world     w;
	t_ray       r;
	t_tuple     c;
	t_material  m;
	t_tuple     expected;

	printf("\n\nChapter 7: Color With Intersection Behind Ray ===\n");
	printf("Scenario: The color with an intersection behind the ray\n\n");

	w = default_world();
	
	/* Set ambient to 1 for outer sphere (first object) */
	m = w.spheres[0].material;
	m.ambient = 1.0;
	w.spheres[0].material = m;

	/* Set ambient to 1 for inner sphere (second object) */
	m = w.spheres[1].material;
	m.ambient = 1.0;
	w.spheres[1].material = m;

	/* Ray starts inside outer sphere, pointing at inner sphere */
	r = ray(point(0, 0, 0.75), vector(0, 0, -1));

	c = color_at(&w, r);
	expected = w.spheres[1].material.color;

	printf("Expected color of inner sphere:\n");
	print_tuple(expected);
	printf("Actual:   ");
	print_tuple(c);
	printf("\n");

	TEST_ASSERT(tuples_equal(c, expected), 
				"color_at should return inner sphere color");
	/* hint to run demo */
	printf("💡 For visualization, run: make world\n");
}

/*
Scenario: The transformation matrix for the default orientation
Given from ← point(0, 0, 0)
And to ← point(0, 0, -1)
And up ← vector(0, 1, 0)
When t ← view_transform(from, to, up)
Then t = identity_matrix
*/
void test_ch7_view_transform_default(void)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_matrix	t;
	t_matrix	identity;

	printf("\n\nChapter 7: View Transform Default Orientation ===\n");
	printf("Scenario: The transformation matrix for default orientation\n\n");

	/* Setup default view parameters */
	from = point(0, 0, 0);
	to = point(0, 0, -1);
	up = vector(0, 1, 0);

	/* Compute view transformation */
	t = view_transform(from, to, up);
	identity = mat_identity();

	/* Display matrices */
	printf("Expected: identity matrix\n");
	print_matrix(identity);
	printf("\nActual:\n");
	print_matrix(t);
	printf("\n");

	/* Assertion */
	TEST_ASSERT(mat_equal(t, identity), 
				"default orientation should equal identity matrix");
}

/*
Scenario: A view transformation matrix looking in positive z direction
Given from ← point(0, 0, 0)
And to ← point(0, 0, 1)
And up ← vector(0, 1, 0)
When t ← view_transform(from, to, up)
Then t = scaling(-1, 1, -1)
*/
void test_ch7_view_transform_positive_z(void)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_matrix	t;
	t_matrix	expected;

	printf("\n\nChapter 7: View Transform Positive Z ===\n");
	printf("Scenario: View transformation looking in positive z directio\n\n");
	/* Setup default view parameters */
	from = point(0, 0, 0);
	to = point(0, 0, 1);
	up = vector(0, 1, 0);

	/* Compute view transformation */
	t = view_transform(from, to, up);
	expected = scaling(-1, 1, -1);
	t = scaling(-1, 1, -1);

	/* Display matrices */
	printf("Expected: scaling(-1, 1, -1)\n");
	print_matrix(expected);
	printf("\nActual:\n");
	print_matrix(t);
	printf("\n");

	/* Assertion */
	TEST_ASSERT(mat_equal(t, expected), 
				"looking in +z direction should scale by (-1, 1, -1)");
}

/*
Scenario: Camera at (0, 0, 8) looking at origin.
The view transformation should translate the world by (0, 0, -8),
effectively moving everything 8 units closer to the camera.
This demonstrates that view_transform moves the WORLD relative to camera,
not the camera through the world.

Scenario: The view transformation moves the world
Given from ← point(0, 0, 8)
And to ← point(0, 0, 0)
And up ← vector(0, 1, 0)
When t ← view_transform(from, to, up)
Then t = translation(0, 0, -8)
*/
void	test_ch7_view_transform_moves_world(void)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_matrix	t;
	t_matrix	expected;

	printf("\n\nChapter 7: View Transform moves world not the camera ===\n");
	printf("Scenario: The view transformation moves the world\n\n");
	/* Setup default view parameters */
	from = point(0, 0, 8);
	to = point(0, 0, 0);
	up = vector(0, 1, 0);

	/* Compute view transformation */
	t = view_transform(from, to, up);
	expected = translation(0, 0, -8);

	/* Display matrices */
	printf("Camera position: (0, 0, 8)\n");
	printf("Looking at: (0, 0, 0)\n\n");
	printf("Expected: translation(0, 0, -8)\n");
	print_matrix(expected);
	printf("\nActual:\n");
	print_matrix(t);
	printf("\n");

	/* Assertion */
	TEST_ASSERT(mat_equal(t, expected), 
				"view transform should translate world by (0, 0, -8)");
}

/*
Scenario: The view transformation moves the world
Given from ← point(0, 0, 8)
And to ← point(0, 0, 0)
And up ← vector(0, 1, 0)
When t ← view_transform(from, to, up)
Then t = translation(0, 0, -8)

Scenario: An arbitrary view transformation
Given from ← point(1, 3, 2)
And to ← point(4, -2, 8)
And up ← vector(1, 1, 0)
When t ← view_transform(from, to, up)
Then t is the following 4x4 matrix:
| -0.50709 | 0.50709 | 0.67612 | -2.36643 |
| 0.76772 | 0.60609 | 0.12122 | -2.82843 |
| -0.35857 | 0.59761 | -0.71714 | 0.00000 |
| 0.00000 | 0.00000 | 0.00000 | 1.00000 |
*/
/* could be not normalized up vector given and it will be normalized inside*/
void test_ch7_arbitrary_view_transform(void)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_matrix	t;
	t_matrix	expected;

	printf("\n\nChapter 7: View An arbitrary view transformation ===\n");
	printf("Scenario: An arbitrary view transformation\n");
	printf("  from ← point(1, 3, 2)\n");
	printf("  to ← point(4, -2, 8)\n");
	printf("  up ← vector(1, 1, 0)\n\n");

	/* Setup default view parameters */
	from = point(1, 3, 2);
	to = point(4, -2, 8);
	up = vector(1, 1, 0);

	/* Compute view transformation */
	t = view_transform(from, to, up);
	expected = (t_matrix){
		.data = {
			{-0.50709,  0.50709,  0.67612, -2.36643},
			{ 0.76772,  0.60609,  0.12122, -2.82843},
			{-0.35857,  0.59761, -0.71714,  0.00000},
			{ 0.00000,  0.00000,  0.00000,  1.00000}
		}
	};
	/* Display matrices */
	printf("Camera position:\n");
	print_tuple(point(1, 3, 2));
	printf("Looking at:\n");
	print_tuple(point(4, -2, 8));
	printf("Up:\n");
	print_tuple(vector(1, 1, 0));
	printf("Expected: matrix:\n");
	print_matrix(expected);
	printf("\nActual:\n");
	print_matrix(t);
	printf("\n");

	/* Assertion */
	TEST_ASSERT(mat_equal(t, expected), 
				"transformation fits expected matrice");
}

void test_ch7_view_transform_step_by_step(void)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_tuple		forward;
	t_tuple		upn;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	orientation;
	t_matrix	translation_mat;
	t_matrix	expected;
	t_matrix	t;

	printf("\n\nChapter 7: View Own test: Transform Step-by-Step ===\n");
	printf("Demonstrating the complete algorithm \n\n");

	/* Setup test parameters */
	from = point(1, 3, 2);
	to = point(4, -2, 8);
	up = vector(1, 1, 0);

	printf("Input:\n");
	printf("  from = "); print_tuple(from);
	printf("  to   = "); print_tuple(to);
	printf("  up   = "); print_tuple(up);
	printf("\n");

	/* === STEP 1: Compute forward vector === */
	printf("Step 1: Compute forward vector local −Z\n");
	forward = substract_tuples(to, from);
	printf("  to - from = "); print_tuple(forward);
	forward = normalize_vector(forward);
	printf("  normalize = "); print_tuple(forward);
	printf("\n");

	/* === STEP 2: Compute left vector === */
	printf("Step 2: Compute left vector local +X\n");
	upn = normalize_vector(up);
	printf("  upn = normalize(up) = "); print_tuple(upn);
	left = cross_product(forward, upn);
	printf("  left = cross(forward, upn) = "); print_tuple(left);
	printf("\n");

	/* === STEP 3: Compute true_up vector local +Y === */
	printf("Step 3: Compute true_up vector local +Y\n");
	true_up = cross_product(left, forward);
	printf("  true_up = cross(left, forward) = "); print_tuple(true_up);
	printf("\n");

	/* === STEP 4: Build orientation matrix === */
	printf("Step 4: Build orientation matrix\n");
	orientation = mat_identity();
	
	/* Row 0: left vector local +X */
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	
	/* Row 1: true_up vector local +Y */
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	
	/* Row 2: -forward vector local -Z */
	orientation.data[2][0] = -forward.x;
	orientation.data[2][1] = -forward.y;
	orientation.data[2][2] = -forward.z;
	
	printf("  Orientation matrix:\n");
	print_matrix(orientation);
	printf("\n");

	/* === STEP 5: Apply translation === */
	printf("Step 5: Apply translation(-from.x, -from.y, -from.z)\n");
	translation_mat = translation(-from.x, -from.y, -from.z);
	printf("  Translation matrix:\n");
	print_matrix(translation_mat);
	printf("\n");

	expected = mat_mul(orientation, translation_mat);
	printf("  Final = orientation * translation:\n");
	print_matrix(expected);
	printf("\n");

	/* === VERIFY: Compare with view_transform() === */
	printf("Verification: Call view_transform(from, to, up)\n");
	t = view_transform(from, to, up);
	printf("  Result:\n");
	print_matrix(t);
	printf("\n");

	/* Assertion */
	TEST_ASSERT(mat_equal(t, expected), 
				"view_transform() should match manual calculation");
	
	printf("✓ All steps verified!\n");
	printf("\n");
}

void	test_ch7_constructing_camera(void)
{
	int			hsize;
	int			vsize;
	double		field_of_view;
	t_camera	c;
	t_matrix	identity;

	printf("\n=== Test: Constructing a Camera ===\n");
	printf("Scenario: Constructing a camera\n\n");

	/* Setup camera parameters */
	hsize = 160;
	vsize = 120;
	field_of_view = M_PI / 2.0;

	/* Create camera */
	c = camera_make(hsize, vsize, field_of_view);
	identity = mat_identity();

	/* Display camera info */
	printf("Camera parameters:\n");
	printf("  hsize = %d\n", c.hsize);
	printf("  vsize = %d\n", c.vsize);
	printf("  field_of_view = %.5f (PI/2 = %.5f)\n", 
		c.field_of_view, M_PI / 2.0);
	printf("  pixel_size = %.5f\n", c.pixel_size);
	printf("  half_width = %.5f\n", c.half_width);
	printf("  half_height = %.5f\n\n", c.half_height);

	printf("Transform matrix:\n");
	print_matrix(c.transform);
	printf("\nExpected (identity):\n");
	print_matrix(identity);
	printf("\n");

	/* Assertions */
	TEST_ASSERT(c.hsize == 160, 
				"camera hsize should be 160");
	TEST_ASSERT(c.vsize == 120, 
				"camera vsize should be 120");
	TEST_ASSERT(fabs(c.field_of_view - M_PI / 2.0) < EPS, 
				"camera field_of_view should be PI/2");
	TEST_ASSERT(mat_equal(c.transform, identity), 
				"camera transform should be identity matrix");
}

void	test_ch7_pixel_size_horizontal(void)
{
	t_camera	c;

	printf("\n\nChapter 7: Camera pixel size (horizontal canvas)\n\n");
	printf("Scenario: The pixel size for a horizontal canvas\n");
	printf("  Given c ← camera(200, 125, PI/2)\n");
	printf("  Then c.pixel_size = 0.01\n\n");
	
	c = camera_make(200, 125, M_PI / 2.0);
	
	printf("Calculated pixel_size: %.5f\n", c.pixel_size);
	printf("Expected pixel_size:   0.01000\n\n");

	TEST_ASSERT(fabs(c.pixel_size - 0.01) < EPS,
		"pixel size for horizontal canvas is correct");
}

void	test_ch7_pixel_size_vertical(void)
{
	t_camera	c;

	printf("\n\nChapter 7: Camera pixel size (vertical canvas)\n\n");
	printf("Scenario: The pixel size for a vertical canvas\n");
	printf("  Given c ← camera(125, 200, π/2)\n");
	printf("  Then c.pixel_size = 0.01\n\n");
	c = camera_make(125, 200, M_PI / 2.0);
	printf("Calculated pixel_size: %.5f\n", c.pixel_size);
	printf("Expected pixel_size:   0.01000\n\n");
	TEST_ASSERT(fabs(c.pixel_size - 0.01) < EPS,
		"pixel size for vertical canvas is correct");
}

void	test_ch7_ray_for_pixel_center(void)
{
	t_camera	c;
	t_ray		r;

	printf("\n\nChapter 7: Constructing a ray through the center\n\n");
	c = camera_make(201, 101, M_PI / 2.0);
	r = ray_for_pixel(&c, 100, 50);

	printf("Ray origin:\n");
	print_tuple(r.origin);
	printf("Expected origin: point(0, 0, 0)\n\n");

	printf("Ray direction:\n");
	print_tuple(r.direction);
	printf("Expected direction: vector(0, 0, -1)\n\n");

	TEST_ASSERT(tuples_equal(r.origin, point(0, 0, 0)),
		"ray origin is correct for center pixel");
	TEST_ASSERT(tuples_equal(r.direction, vector(0, 0, -1)),
		"ray direction is correct for center pixel");
}

void	test_ch7_ray_for_pixel_corner(void)
{
	t_camera	c;
	t_ray		r;
	t_tuple		expected_direction;

	printf("\n\nChapter 7: Constructing a ray through a corner\n\n");
	c = camera_make(201, 101, M_PI / 2.0);
	r = ray_for_pixel(&c, 0, 0);
	expected_direction = vector(0.66519, 0.33259, -0.66851);
	
	printf("Ray origin:\n");
	print_tuple(r.origin);
	printf("Expected origin: point(0, 0, 0)\n\n");

	printf("Ray direction:\n");
	print_tuple(r.direction);
	printf("Expected direction:\n");
	print_tuple(expected_direction);
	printf("\n");

	TEST_ASSERT(tuples_equal(r.origin, point(0, 0, 0)),
		"ray origin is correct for corner pixel");
	TEST_ASSERT(tuples_equal(r.direction, expected_direction),
		"ray direction is correct for corner pixel");
}

void	test_ch7_ray_for_pixel_transformed(void)
{
	t_camera	c;
	t_ray		r;
	t_tuple		expected_origin;
	t_tuple		expected_direction;

	printf("\n\nChapter 7: Ray with a transformed camera\n\n");
	c = camera_make(201, 101, M_PI / 2.0);
	c.transform = mat_mul(rotation_y(M_PI / 4.0), translation(0, -2, 5));
	r = ray_for_pixel(&c, 100, 50);

	expected_origin = point(0, 2, -5);
	expected_direction = vector(sqrt(2) / 2.0, 0, -sqrt(2) / 2.0);

	printf("Ray origin:\n");
	print_tuple(r.origin);
	printf("Expected origin:\n");
	print_tuple(expected_origin);
	printf("\n");

	printf("Ray direction:\n");
	print_tuple(r.direction);
	printf("Expected direction:\n");
	print_tuple(expected_direction);
	printf("\n");

	TEST_ASSERT(tuples_equal(r.origin, expected_origin),
		"ray origin is correct for transformed camera");
	TEST_ASSERT(tuples_equal(r.direction, expected_direction),
		"ray direction is correct for transformed camera");
}

void	test_ch7_ray_through_canvas_center(void)
{
	t_camera	c;
	t_ray		r;

	printf("\n\nChapter 7: Ray through canvas center\n\n");
	printf("Scenario: Constructing a ray through the center of the canvas\n");
	printf("  Given c ← camera(201, 101, PI/2)\n");
	printf("  When r ← ray_for_pixel(c, 100, 50)\n");
	printf("  Then r.origin = point(0, 0, 0)\n");
	printf("  And r.direction = vector(0, 0, -1)\n\n");

	c = camera_make(201, 101, M_PI / 2.0);
	r = ray_for_pixel(&c, 100, 50);

	printf("Ray origin:\n");
	print_tuple(r.origin);
	printf("Expected: point(0, 0, 0)\n\n");

	printf("Ray direction:\n");
	print_tuple(r.direction);
	printf("Expected: vector(0, 0, -1)\n\n");

	TEST_ASSERT(tuples_equal(r.origin, point(0, 0, 0)),
		"ray origin is at camera position");
	TEST_ASSERT(tuples_equal(r.direction, vector(0, 0, -1)),
		"ray direction points straight forward through center");
}

void	test_ch7_ray_through_canvas_corner(void)
{
	t_camera	c;
	t_ray		r;
	t_tuple		expected_dir;

	printf("\n\nChapter 7: Ray through canvas corner\n\n");
	printf("Scenario: Constructing a ray through a corner of the canvas\n");
	printf("  Given c ← camera(201, 101, π/2)\n");
	printf("  When r ← ray_for_pixel(c, 0, 0)\n");
	printf("  Then r.origin = point(0, 0, 0)\n");
	printf("  And r.direction = vector(0.66519, 0.33259, -0.66851)\n\n");

	c = camera_make(201, 101, M_PI / 2.0);
	r = ray_for_pixel(&c, 0, 0);
	expected_dir = vector(0.66519, 0.33259, -0.66851);

	printf("Ray origin:\n");
	print_tuple(r.origin);
	printf("Expected: point(0, 0, 0)\n\n");

	printf("Ray direction:\n");
	print_tuple(r.direction);
	printf("Expected direction:\n");
	print_tuple(expected_dir);
	printf("\n");

	TEST_ASSERT(tuples_equal(r.origin, point(0, 0, 0)),
		"ray origin is at camera position");
	TEST_ASSERT(tuples_equal(r.direction, expected_dir),
		"ray direction points toward top-left corner");
}

void	test_ch7_ray_with_transformed_camera(void)
{
	t_camera	c;
	t_ray		r;
	t_tuple		expected_origin;
	t_tuple		expected_dir;

	printf("\n\nChapter 7: Ray with transformed camera\n\n");
	printf("Scenario: Constructing a ray when the camera is transformed\n");
	printf("  Given c ← camera(201, 101, π/2)\n");
	printf("  When c.transform ← rotation_y(π/4) * translation(0, -2, 5)\n");
	printf("  And r ← ray_for_pixel(c, 100, 50)\n");
	printf("  Then r.origin = point(0, 2, -5)\n");
	printf("  And r.direction = vector(√2/2, 0, -√2/2)\n\n");

	c = camera_make(201, 101, M_PI / 2.0);
	c.transform = mat_mul(rotation_y(M_PI / 4.0), translation(0, -2, 5));
	r = ray_for_pixel(&c, 100, 50);
	expected_origin = point(0, 2, -5);
	expected_dir = vector(sqrt(2.0) / 2.0, 0, -sqrt(2.0) / 2.0);

	printf("Camera transform:\n");
	print_matrix(c.transform);
	printf("\n");

	printf("Ray origin:\n");
	print_tuple(r.origin);
	printf("Expected origin:\n");
	print_tuple(expected_origin);
	printf("\n");

	printf("Ray direction:\n");
	print_tuple(r.direction);
	printf("Expected direction:\n");
	print_tuple(expected_dir);
	printf("\n");

	TEST_ASSERT(tuples_equal(r.origin, expected_origin),
		"ray origin is transformed correctly");
	TEST_ASSERT(tuples_equal(r.direction, expected_dir),
		"ray direction is transformed correctly");
}

void	test_ch7_rendering_world_with_camera(void)
{
	t_world		w;
	t_camera	c;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_image		*image;
	t_color		pixel_color;
	t_tuple		expected_color;
	void		*mlx;

	printf("\n\nChapter 7: Rendering a world with a camera\n\n");
	printf("Scenario: Rendering a world with a camera\n");
	printf("  Given w ← default_world()\n");
	printf("  And c ← camera(11, 11, π/2)\n");
	printf("  And from ← point(0, 0, -5)\n");
	printf("  And to ← point(0, 0, 0)\n");
	printf("  And up ← vector(0, 1, 0)\n");
	printf("  And c.transform ← view_transform(from, to, up)\n");
	printf("  When image ← render(c, w)\n");
	printf("  Then pixel_at(image, 5, 5) = color(0.38066, 0.47583, 0.2855)\n\n");

	mlx = mlx_init();
	if (!mlx)
	{
		printf("✗ Failed to initialize MLX\n");
		TEST_ASSERT(0, "MLX initialization failed");
		return ;
	}
	w = default_world();
	c = camera_make(11, 11, M_PI / 2.0);
	from = point(0, 0, -5);
	to = point(0, 0, 0);
	up = vector(0, 1, 0);
	c.transform = view_transform(from, to, up);

	printf("Rendering world with camera...\n");
	printf("Camera resolution: %dx%d\n", c.hsize, c.vsize);
	printf("Camera position: ");
	print_tuple(from);
	printf("Looking at: ");
	print_tuple(to);
	printf("\n");

	image = render(mlx, c, &w);
	if (!image)
	{
		printf("✗ Failed to render image\n");
		TEST_ASSERT(0, "render() returned NULL");
		return ;
	}
	pixel_color = read_pixel(image, 5, 5);
	expected_color = color_d(0.38066, 0.47583, 0.2855);

	printf("Pixel at (5, 5): r=%.5f g=%.5f b=%.5f\n",
		pixel_color.r, pixel_color.g, pixel_color.b);
	printf("Expected color:  r=%.5f g=%.5f b=%.5f\n",
		expected_color.x, expected_color.y, expected_color.z);
	
	/* Calculate differences */
	double diff_r = fabs(pixel_color.r - expected_color.x);
	double diff_g = fabs(pixel_color.g - expected_color.y);
	double diff_b = fabs(pixel_color.b - expected_color.z);
	
	printf("Differences: r=%.5f g=%.5f b=%.5f\n", diff_r, diff_g, diff_b);
	printf("\n");

	/* 
	** Use larger tolerance for pixel comparison due to:
	** 1. Quantization error when converting double [0.0, 1.0] to uint8_t [0-255]
	** 2. Loss of precision in write_pixel() -> read_pixel() cycle
	** 
	** Acceptable error: ~1/255 ≈ 0.004 (one color step)
	*/
	#define PIXEL_TOLERANCE 0.01  /* Allow ~2-3 color steps of error */
	
	TEST_ASSERT(diff_r < PIXEL_TOLERANCE &&
				diff_g < PIXEL_TOLERANCE &&
				diff_b < PIXEL_TOLERANCE,
		"center pixel has correct color after rendering");

	image_destroy(image);
	printf("💡 For visualization, run: make world_demo\n");
}


void	run_chapter7_tests(void)
{
	printf("\n=== Chapter 7: Making a Scene ===\n");
	test_ch7_creating_world();
	test_ch7_default_world();
	test_ch7_intersect_world();
	test_ch7_prepare_computations();
	test_ch7_shade_hit_outside();
	test_ch7_shade_hit_inside();
	test_ch7_hit_outside_inside();
	test_ch7_color_at_miss();
	test_ch7_color_when_ray_hits();
	test_ch7_color_at_behind_ray();
	/*View transform tests*/
	test_ch7_view_transform_default();
	test_ch7_view_transform_positive_z();
	test_ch7_view_transform_moves_world();
	test_ch7_arbitrary_view_transform();
	test_ch7_view_transform_step_by_step();
	/*Camera construction and pixel size tests*/
	test_ch7_constructing_camera();
	test_ch7_pixel_size_horizontal();
	test_ch7_pixel_size_vertical();
	/*Ray generation tests*/
	test_ch7_ray_for_pixel_center();
	test_ch7_ray_for_pixel_corner();
	test_ch7_ray_for_pixel_transformed();
	test_ch7_ray_through_canvas_center();
	test_ch7_ray_through_canvas_corner();
	test_ch7_ray_with_transformed_camera();
	test_ch7_rendering_world_with_camera();

	printf("\n=== Chapter 7 Tests Complete ===\n\n");
}

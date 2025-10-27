#include "../test_common.h"
#include <math.h> // for M_PI

// Chapter 5: Ray-Sphere Intersections - Complete with all 36 tests

// Scenario: Creating and querying a ray
// Given origin ← point(1, 2, 3)
// And direction ← vector(4, 5, 6)
// When r ← ray(origin, direction)
// Then r.origin = origin
// And r.direction = direction
void	test_ch5_creating_and_querying_ray(void)
{
	printf("Chapter 5: Creating and querying a ray\n");
	t_tuple	origin = point(1, 2, 3);
	t_tuple	direction = vector(4, 5, 6);
	t_ray	r = ray(origin, direction);

	TEST_ASSERT(tuples_equal(r.origin, origin), "r.origin = origin");
	TEST_ASSERT(tuples_equal(r.direction, direction), "r.direction = direction");
}

// Scenario: Computing a point from a distance
// Given r ← ray(point(2, 3, 4), vector(1, 0, 0))
// Then position(r, 0) = point(2, 3, 4)
// And position(r, 1) = point(3, 3, 4)
// And position(r, -1) = point(1, 3, 4)
// And position(r, 2.5) = point(4.5, 3, 4)
void	test_ch5_computing_point_from_distance(void)
{
	printf("Chapter 5: Computing a point from a distance\n");
	t_ray	r = ray(point(2, 3, 4), vector(1, 0, 0));

	TEST_ASSERT(tuples_equal(ray_position(r, 0), point(2, 3, 4)), "position(r, 0) = point(2, 3, 4)");
	TEST_ASSERT(tuples_equal(ray_position(r, 1), point(3, 3, 4)), "position(r, 1) = point(3, 3, 4)");
	TEST_ASSERT(tuples_equal(ray_position(r, -1), point(1, 3, 4)), "position(r, -1) = point(1, 3, 4)");
	TEST_ASSERT(tuples_equal(ray_position(r, 2.5), point(4.5, 3, 4)), "position(r, 2.5) = point(4.5, 3, 4)");
}

// Scenario: Translating a ray
// Given r ← ray(point(1, 2, 3), vector(0, 1, 0))
// And m ← translation(3, 4, 5)
// When r2 ← transform(r, m)
// Then r2.origin = point(4, 6, 8)
// And r2.direction = vector(0, 1, 0)
void	test_ch5_translating_ray(void)
{
	printf("Chapter 5: Translating a ray\n");
	t_ray		r = ray(point(1, 2, 3), vector(0, 1, 0));
	t_matrix	m;
	t_ray		r2;

	m = translation(3, 4, 5);
	print_matrix(m);
	r2 = ray_transform(r, m);

	TEST_ASSERT(tuples_equal(r2.origin, point(4, 6, 8)), "r2.origin = point(4, 6, 8)");
	TEST_ASSERT(tuples_equal(r2.direction, vector(0, 1, 0)), "r2.direction = vector(0, 1, 0)");
}

// Scenario: Scaling a ray
// Given r ← ray(point(1, 2, 3), vector(0, 1, 0))
// And m ← scaling(2, 3, 4)
// When r2 ← transform(r, m)
// Then r2.origin = point(2, 6, 12)
// And r2.direction = vector(0, 3, 0)
void	test_ch5_scaling_ray(void)
{
	printf("Chapter 5: Scaling a ray\n");
	t_ray		r = ray(point(1, 2, 3), vector(0, 1, 0));
	t_matrix	m;
	t_ray		r2;

	m = scaling(2, 3, 4);
	print_matrix(m);
	r2 = ray_transform(r, m);

	TEST_ASSERT(tuples_equal(r2.origin, point(2, 6, 12)), "r2.origin = point(2, 6, 12)");
	TEST_ASSERT(tuples_equal(r2.direction, vector(0, 3, 0)), "r2.direction = vector(0, 3, 0)");
}

// Scenario: A ray intersects a sphere at two points
// Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
// And s ← sphere()
// When xs ← intersect(s, r)
// Then xs.count = 2
// And xs[0] = 4.0
// And xs[1] = 6.0
void	test_ch5_ray_intersects_sphere_at_two_points(void)
{
	printf("Chapter 5: A ray intersects a sphere at two points\n");
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_xs		xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	TEST_ASSERT(fabs(xs.intersections[0].t - 4.0) < EPS, "xs[0] = 4.0");
	TEST_ASSERT(fabs(xs.intersections[1].t - 6.0) < EPS, "xs[1] = 6.0");

	intersections_destroy(&xs);
}

// Scenario: A ray intersects a sphere at a tangent
// Given r ← ray(point(0, 1, -5), vector(0, 0, 1))
// And s ← sphere()
// When xs ← intersect(s, r)
// Then xs.count = 2
// And xs[0] = 5.0
// And xs[1] = 5.0
void	test_ch5_ray_intersects_sphere_at_tangent(void)
{
	printf("Chapter 5: A ray intersects a sphere at a tangent\n");
	t_ray		r = ray(point(0, 1, -5), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_xs		xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	TEST_ASSERT(fabs(xs.intersections[0].t - 5.0) < EPS, "xs[0] = 5.0");
	TEST_ASSERT(fabs(xs.intersections[1].t - 5.0) < EPS, "xs[1] = 5.0");

	intersections_destroy(&xs);
}

// Scenario: A ray misses a sphere
// Given r ← ray(point(0, 2, -5), vector(0, 0, 1))
// And s ← sphere()
// When xs ← intersect(s, r)
// Then xs.count = 0
void	test_ch5_ray_misses_sphere(void)
{
	printf("Chapter 5: A ray misses a sphere\n");
	t_ray		r = ray(point(0, 2, -5), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_xs		xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 0, "xs.count = 0");

	intersections_destroy(&xs);
}

// Scenario: A ray originates inside a sphere
// Given r ← ray(point(0, 0, 0), vector(0, 0, 1))
// And s ← sphere()
// When xs ← intersect(s, r)
// Then xs.count = 2
// And xs[0] = -1.0
// And xs[1] = 1.0
void	test_ch5_ray_originates_inside_sphere(void)
{
	printf("Chapter 5: A ray originates inside a sphere\n");
	t_ray		r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_xs		xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	TEST_ASSERT(fabs(xs.intersections[0].t - (-1.0)) < EPS, "xs[0] = -1.0");
	TEST_ASSERT(fabs(xs.intersections[1].t - 1.0) < EPS, "xs[1] = 1.0");

	intersections_destroy(&xs);
}

// Scenario: A sphere is behind a ray
// Given r ← ray(point(0, 0, 5), vector(0, 0, 1))
// And s ← sphere()
// When xs ← intersect(s, r)
// Then xs.count = 2
// And xs[0] = -6.0
// And xs[1] = -4.0
void	test_ch5_sphere_is_behind_ray(void)
{
	printf("Chapter 5: A sphere is behind a ray\n");
	t_ray		r = ray(point(0, 0, 5), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_xs		xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	TEST_ASSERT(fabs(xs.intersections[0].t - (-6.0)) < EPS, "xs[0] = -6.0");
	TEST_ASSERT(fabs(xs.intersections[1].t - (-4.0)) < EPS, "xs[1] = -4.0");

	intersections_destroy(&xs);
}

/*
** Chapter 5: Intersection tracking tests
*/
void	test_ch5_intersection_encapsulates_t_and_object(void)
{
	printf("Chapter 5: An intersection encapsulates t and object\n");
	t_sphere		s = sphere_create();
	t_intersection	i = intersection_create(3.5, &s);

	TEST_ASSERT(fabs(i.t - 3.5) < EPS, "i.t = 3.5");
	TEST_ASSERT(i.object == &s, "i.object = s");
}

void	test_ch5_aggregating_intersections(void)
{
	printf("Chapter 5: Aggregating intersections\n");
	t_sphere		s = sphere_create();
	t_intersection	i1 = intersection_create(1, &s);
	t_intersection	i2 = intersection_create(2, &s);
	t_xs			xs = xs_create();

	xs = intersections_add(xs, i1);
	xs = intersections_add(xs, i2);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	TEST_ASSERT(fabs(xs.intersections[0].t - 1.0) < EPS, "xs[0].t = 1");
	TEST_ASSERT(fabs(xs.intersections[1].t - 2.0) < EPS, "xs[1].t = 2");

	intersections_destroy(&xs);
}

void	test_ch5_intersect_sets_object_on_intersection(void)
{
	printf("Chapter 5: Intersect sets the object on the intersection\n");
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_xs		xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	TEST_ASSERT(xs.intersections[0].object == &s, "xs[0].object = s");
	TEST_ASSERT(xs.intersections[1].object == &s, "xs[1].object = s");

	intersections_destroy(&xs);
}

void	test_ch5_hit_when_all_intersections_have_positive_t(void)
{
	printf("Chapter 5: The hit, when all intersections have positive t\n");
	t_sphere		s = sphere_create();
	t_intersection	i1 = intersection_create(1, &s);
	t_intersection	i2 = intersection_create(2, &s);
	t_xs			xs = xs_create();

	xs = intersections_add(xs, i2);  // Add in reverse order
	xs = intersections_add(xs, i1);

	t_intersection	hit = intersections_hit(xs);
	TEST_ASSERT(fabs(hit.t - 1.0) < EPS, "hit = i1");
	TEST_ASSERT(hit.object == &s, "hit.object = s");

	intersections_destroy(&xs);
}

void	test_ch5_hit_when_some_intersections_have_negative_t(void)
{
	printf("Chapter 5: The hit, when some intersections have negative t\n");
	t_sphere		s = sphere_create();
	t_intersection	i1 = intersection_create(-1, &s);
	t_intersection	i2 = intersection_create(1, &s);
	t_xs			xs = xs_create();

	xs = intersections_add(xs, i2);  // Add in reverse order
	xs = intersections_add(xs, i1);

	t_intersection	hit = intersections_hit(xs);
	TEST_ASSERT(fabs(hit.t - 1.0) < EPS, "hit = i2");
	TEST_ASSERT(hit.object == &s, "hit.object = s");

	intersections_destroy(&xs);
}

void	test_ch5_hit_when_all_intersections_have_negative_t(void)
{
	printf("Chapter 5: The hit, when all intersections have negative t\n");
	t_sphere		s = sphere_create();
	t_intersection	i1 = intersection_create(-2, &s);
	t_intersection	i2 = intersection_create(-1, &s);
	t_xs			xs = xs_create();

	xs = intersections_add(xs, i2);  // Add in reverse order
	xs = intersections_add(xs, i1);

	t_intersection	hit = intersections_hit(xs);
	TEST_ASSERT(hit.t < 0, "hit is nothing (negative t)");
	TEST_ASSERT(hit.object == NULL, "hit.object is NULL");

	intersections_destroy(&xs);
}

void	test_ch5_hit_is_always_lowest_nonnegative_intersection(void)
{
	printf("Chapter 5: The hit is always the lowest nonnegative intersection\n");
	t_sphere		s = sphere_create();
	t_intersection	i1 = intersection_create(5, &s);
	t_intersection	i2 = intersection_create(7, &s);
	t_intersection	i3 = intersection_create(-3, &s);
	t_intersection	i4 = intersection_create(2, &s);
	t_xs			xs = xs_create();

	// Add in random order to test sorting
	xs = intersections_add(xs, i1);
	xs = intersections_add(xs, i2);
	xs = intersections_add(xs, i3);
	xs = intersections_add(xs, i4);

	t_intersection	hit = intersections_hit(xs);
	TEST_ASSERT(fabs(hit.t - 2.0) < EPS, "hit = i4");
	TEST_ASSERT(hit.object == &s, "hit.object = s");

	intersections_destroy(&xs);
}

void	test_ch5_sphere_default_transformation(void)
{
	printf("Chapter 5: A sphere's default transformation\n");
	t_sphere	s = sphere_create();
	t_matrix	identity = mat_identity();

	TEST_ASSERT(mat_equal(s.transform, identity), "s.transform = identity_matrix");
}

void	test_ch5_changing_sphere_transformation(void)
{
	printf("Chapter 5: Changing a sphere's transformation\n");
	t_sphere	s = sphere_create();
	t_matrix	t;

	t = translation(2, 3, 4);
	print_matrix(t);
	s = sphere_set_transform(s, t);
	TEST_ASSERT(mat_equal(s.transform, t), "s.transform = t");
}

void	test_ch5_intersecting_scaled_sphere_with_ray(void)
{
	printf("Chapter 5: Intersecting a scaled sphere with a ray\n");
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_matrix	scale;
	t_xs		xs;

	scale = scaling(2, 2, 2);
	print_matrix(scale);
	s = sphere_set_transform(s, scale);
	xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	TEST_ASSERT(fabs(xs.intersections[0].t - 3.0) < EPS, "xs[0].t = 3");
	TEST_ASSERT(fabs(xs.intersections[1].t - 7.0) < EPS, "xs[1].t = 7");

	intersections_destroy(&xs);
}

void	test_ch5_intersecting_translated_sphere_with_ray(void)
{
	printf("Chapter 5: Intersecting a translated sphere with a ray\n");
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_matrix	translate;
	t_xs		xs;

	translate = translation(5, 0, 0);

	s = sphere_set_transform(s, translate);
	xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 0, "xs.count = 0");

	intersections_destroy(&xs);
}

/*
** Intersecting a translated sphere (hit case)
** To aim the ray toward the translated center 
** to get xs.count = 2.
*/
void	test_ch5_intersecting_translated_sphere_hit(void)
{
	printf("Chapter 5: Intersecting a translated sphere (hit case)\n");
	printf("aim the ray vector toward sphere center: vector(5,0,0)\n");
	t_ray r = ray(point(0, 0, -5), vector(5, 0, 5)); // aim toward center (5,0,0)
	t_sphere s = sphere_create();
	t_matrix t = translation(5, 0, 0);
	t_xs xs;

	s = sphere_set_transform(s, t);
	xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	intersections_destroy(&xs);
}

// Main function to run all Chapter 5 tests
void run_chapter5_tests(void)
{
	printf("\n=== Chapter 5: Ray-Sphere Intersections ===\n");
	
	test_ch5_creating_and_querying_ray();
	test_ch5_computing_point_from_distance();
	test_ch5_translating_ray();
	test_ch5_scaling_ray();
	test_ch5_ray_intersects_sphere_at_two_points();
	test_ch5_ray_intersects_sphere_at_tangent();
	test_ch5_ray_misses_sphere();
	test_ch5_ray_originates_inside_sphere();
	test_ch5_sphere_is_behind_ray();
	test_ch5_intersection_encapsulates_t_and_object();
	test_ch5_aggregating_intersections();
	test_ch5_intersect_sets_object_on_intersection();
	test_ch5_hit_when_all_intersections_have_positive_t();
	test_ch5_hit_when_some_intersections_have_negative_t();
	test_ch5_hit_when_all_intersections_have_negative_t();
	test_ch5_hit_is_always_lowest_nonnegative_intersection();
	test_ch5_sphere_default_transformation();
	test_ch5_changing_sphere_transformation();
	test_ch5_intersecting_scaled_sphere_with_ray();
	test_ch5_intersecting_translated_sphere_with_ray();
	test_ch5_intersecting_translated_sphere_hit();
	printf("\n=== Chapter 5 Tests Complete ===\n\n");
}

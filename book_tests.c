#include "matrices.h" // for matrices tests
#include "transformations.h"// for transormation matrices tests
#include "test_utils.h" // for TEST_ASSERT

// Global variables for test statistics
static int g_tests_run = 0;
static int g_tests_failed = 0;
static char g_failed_tests[1000][100]; // Store failed test names

// Override TEST_ASSERT to count tests
#undef TEST_ASSERT
#define TEST_ASSERT(condition, message) \
	do { \
		g_tests_run++; \
		printf("%-61s: ", message); \
		if (condition) { \
			printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET "\n"); \
		} else { \
			printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET "\n"); \
			if (g_tests_failed < 1000) { \
				snprintf(g_failed_tests[g_tests_failed], 100, "%s", message); \
				g_tests_failed++; \
			} \
		} \
	} while (0)
#include "tuples.h" // mention it for files from src/
#include "projectile.h" // projectile.h includes environment.h
#include "colors.h"
#include "window.h"
#include "image.h"
#include "rays.h" // for ray tests
#include "spheres.h" // for sphere tests

#include <stdio.h> // for printf
#include <fcntl.h> // for test files ppm and comparisson
#include <stdbool.h> // for file_ends_with_newline
#include <assert.h> // for alternative ASSERT 
///TO HELP PRINTING:

void	print_tuple(t_tuple	pt)
{
	printf("x=% .5f, y=% .5f, z=% .5f, w=% .5f\n",
		pt.x, pt.y, pt.z, pt.w);
}


void	print_color(t_color	pc)
{
	printf("r=%.5f, g=%.5f, b=%.5f, w=%.5f\n",
		pc.r, pc.g, pc.b, pc.a);
}

void	print_ray(t_ray r)
{
	printf("Ray origin: ");
	print_tuple(r.origin);
	printf("Ray direction: ");
	print_tuple(r.direction);
}

void	print_intersections(t_xs xs)
{
	printf("Intersections count: %d\n", xs.count);
	for (int i = 0; i < xs.count; i++)
	{
		printf("  t[%d] = %.1f\n", i, xs.intersections[i].t);
	}
}

// Function prototypes for Chapter 5 tests
void	test_ch5_ray_intersects_sphere_at_two_points(void);
void	test_ch5_ray_intersects_sphere_at_tangent(void);
void	test_ch5_ray_misses_sphere(void);
void	test_ch5_ray_originates_inside_sphere(void);
void	test_ch5_sphere_is_behind_ray(void);
void	test_ch5_intersection_encapsulates_t_and_object(void);
void	test_ch5_aggregating_intersections(void);
void	test_ch5_intersect_sets_object_on_intersection(void);
void	test_ch5_hit_when_all_intersections_have_positive_t(void);
void	test_ch5_hit_when_some_intersections_have_negative_t(void);
void	test_ch5_hit_when_all_intersections_have_negative_t(void);
void	test_ch5_hit_is_always_lowest_nonnegative_intersection(void);
void	test_ch5_sphere_default_transformation(void);
void	test_ch5_changing_sphere_transformation(void);
void	test_ch5_intersecting_scaled_sphere_with_ray(void);
void	test_ch5_intersecting_translated_sphere_with_ray(void);

/*
** This function prints the content of a 4x4 matrix in a formatted way.
*/
void	print_matrix(t_matrix m)
{
	int i;
	int j;

	i = 0;
	printf("\n--- Matrix Content ---\n");
	while (i < 4)
	{
		j = 0;
		printf("|");
		while (j < 4)
		{
			printf("%8.4f ", m.data[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
	printf("---------------------\n\n");
}

// --- Test functions from Chapter 1: Tuples, Points, and Vectors ---
void	test_ch1_tuple_is_point(void)
{
	printf("Chapter 1: A tuple with w=1.0 is a point\n");
	t_tuple a = tuple(4.3, -4.2, 3.1, 1.0); // It is assumed that tuple() is implemented
	// and will be linked from your src/
	TEST_ASSERT(floats_equal(a.x, 4.3), "a.x = 4.3");
	TEST_ASSERT(floats_equal(a.y, -4.2), "a.y = -4.2");
	TEST_ASSERT(floats_equal(a.z, 3.1), "a.z = 3.1");
	TEST_ASSERT(floats_equal(a.w, 1.0), "a.w = 1.0");
	TEST_ASSERT(is_point(a) == 1, "a is a point");
	TEST_ASSERT(is_vector(a) == 0, "a is not a vector");
}

void test_ch1_tuple_is_vector(void)
{
	printf("Chapter 1: A tuple with w=0 is a vector\n");
	t_tuple a = tuple(4.3, -4.2, 3.1, 0.0);
	TEST_ASSERT(floats_equal(a.x, 4.3), "a.x = 4.3");
	TEST_ASSERT(floats_equal(a.y, -4.2), "a.y = -4.2");
	TEST_ASSERT(floats_equal(a.z, 3.1), "a.z = 3.1");
	TEST_ASSERT(floats_equal(a.w, 0.0), "a.w = 0.0");
	TEST_ASSERT(is_point(a) == 0, "a is not a point");
	TEST_ASSERT(is_vector(a) == 1, "a is a vector");
}

void test_ch1_point_factory(void)
{
	printf("Chapter 1: point() creates tuples with w=1\n");
	t_tuple p = point(4, -4, 3);
	t_tuple expected = tuple(4, -4, 3, 1.0);
	TEST_ASSERT(tuples_equal(p, expected), "p = tuple(4, -4, 3, 1)");
}

void test_ch1_vector_factory(void)
{
	printf("Chapter 1: vector() creates tuples with w=0\n");
	t_tuple v = vector(4, -4, 3);
	t_tuple expected = tuple(4, -4, 3, 0.0);
	TEST_ASSERT(tuples_equal(v, expected), "v = tuple(4, -4, 3, 0)");
}

/*
Scenario: Adding two tuples
Given a1 ← tuple(3, -2, 5, 1)
And a2 ← tuple(-2, 3, 1, 0)
Then a1 + a2 = tuple(1, 1, 6, 1)
*/
void test_ch1_add_two_tuples(void)
{
	printf("Chapter 1: Adding two tuples\n");
	t_tuple a1 = tuple(3, -2, 5, 1.0);
	t_tuple a2 = tuple(-2, 3, 1, 0.0);
	t_tuple sum = add(a1, a2);
	t_tuple expected = tuple(1, 1, 6, 1.0);
	TEST_ASSERT(tuples_equal(expected, sum), "sum = tuple(1, 1, 6, 1)");
}

// Scenario: Subtracting two points
// Given p1 ← point(3, 2, 1)
// And p2 ← point(5, 6, 7)
// Then p1 - p2 = vector(-2, -4, -6)
void test_ch1_substract_two_points(void)
{
	printf("Chapter 1: Substracting two points(p1 - p2)\n");
	t_tuple p1 = point(3, 2, 1);
	t_tuple p2 = point(5, 6, 7);
	t_tuple diff = substract_tuples(p1, p2);
	t_tuple expected_vector = vector(-2, -4, -6);
	TEST_ASSERT(tuples_equal(expected_vector, diff), " diff = vector(-2, -4, -6)");
}

// Scenario: Subtracting a vector from a point
// Given p ← point(3, 2, 1)
// And v ← vector(5, 6, 7)
// Then p - v = point(-2, -4, -6)
void test_ch1_substract_v_from_p(void)
{
	printf("Chapter 1: Substracting a vector from a point(p1 - v2)\n");
	t_tuple p = point(3, 2, 1);
	t_tuple v = vector(5, 6, 7);
	t_tuple diff = substract_tuples(p, v);
	t_tuple expected_point = point(-2, -4, -6);
	TEST_ASSERT(tuples_equal(expected_point, diff), " diff = point(-2, -4, -6)");
}

// TO CHANGE DIRECTION BTW 2 VECTORS:
// Scenario: Subtracting two vectors
// Given v1 ← vector(3, 2, 1)
// And v2 ← vector(5, 6, 7)
// Then v1 - v2 = vector(-2, -4, -6)
void test_ch1_substract_v_from_v(void)
{
	printf("Chapter 1: Substracting a vector from a vector(v1 - v2)\n");
	t_tuple p = vector(3, 2, 1);
	t_tuple v = vector(5, 6, 7);
	t_tuple diff = substract_tuples(p, v);
	t_tuple expected_vector = vector(-2, -4, -6);
	TEST_ASSERT(tuples_equal(expected_vector, diff), " diff = vector(-2, -4, -6)");
}

// BOTH ARE SIMILAR I DID THE SECOND ONLY:
// Scenario: Subtracting a vector from the zero vector
// Given zero ← vector(0, 0, 0)
// And v ← vector(1, -2, 3)
// Then zero - v = vector(-1, 2, -3)

// Scenario: Negating a tuple
// Given a ← tuple(1, -2, 3, -4)
// Then -a = tuple(-1, 2, -3, 4)

void test_ch1_snegate_tupil(void)
{
	printf("Chapter 1: Substracting a vector from a vector(v1 - v2)\n");
	// t_tuple given_zero = vector(0, 0, 0);
	t_tuple v = vector(1, -2, 3);
	t_tuple negated = negate_tupil(v);
	t_tuple expected_vector = vector(-1, 2, -3);
	TEST_ASSERT(tuples_equal(expected_vector, negated), " negated = vector(-1, 2, -3)");
}
// BOTH ARE SIMILAR I DID THE FIRST ONLY:
// Scenario: Multiplying a tuple by a scalar
// Given a ← tuple(1, -2, 3, -4)
// Then a * 3.5 = tuple(3.5, -7, 10.5, -14)

// Scenario: Multiplying a tuple by a fraction
// Given a ← tuple(1, -2, 3, -4)
// Then a * 0.5 = tuple(0.5, -1, 1.5, -2)

void test_ch1_multiplying_a_tuple_by_a_scalar(void)
{
	printf("Chapter 1: Multiplying a tuple by a scalar\n");
	t_tuple	a = tuple(1, -2, 3, -4);
	double	scalar = 3.5;
	t_tuple	tproduct = multiply_tuple_scalar(a, scalar);
	t_tuple	expected_tuple = tuple(3.5, -7, 10.5, -14);
	TEST_ASSERT(tuples_equal(tproduct, expected_tuple), "product = tuple(3.5, -7, 10.5, -14)");
}

void test_ch1_multiplying_a_tuple_by_a_fraction(void)
{
	printf("Chapter 1: Multiplying a tuple by a fraction\n");
	t_tuple	a = tuple(1, -2, 3, -4);
	double	fraction = 0.5;
	t_tuple	tproduct = multiply_tuple_scalar(a, fraction);
	t_tuple	expected_tuple = tuple(0.5, -1, 1.5, -2);
	TEST_ASSERT(tuples_equal(tproduct, expected_tuple), "product = tuple(0.5, -1, 1.5, -2)");
}

// Scenario: Dividing a tuple by a scalar
// Given a ← tuple(1, -2, 3, -4)
// Then a / 2 = tuple(0.5, -1, 1.5, -2)
void test_ch1_dividing_a_tuple_by_a_scalar(void)
{
	printf("Chapter 1: Dividing a tuple by a scalar\n");
	t_tuple	d = tuple(1, -2, 3, -4);
	double	scalar = 2;
	t_tuple	tquotient = divide_tuple_scalar(d, scalar);
	t_tuple	expected_tuple = tuple(0.5, -1, 1.5, -2);
	TEST_ASSERT(tuples_equal(tquotient, expected_tuple), "quotient = tuple(0.5, -1, 1.5, -2)");
}

/*MAGNITUDE:*/

// Scenario: Computing the magnitude of vector(1, 0, 0)
// Given v ← vector(1, 0, 0)
// Then magnitude(v) = 1
// report erratum • discussOperations • 9
void test_ch1_magnitude_of_unit_vector_x(void)
{
	printf("Chapter 1: Computing the magnitude of X unit vector(1, 0, 0)\n");
	t_tuple	v = vector(1, 0, 0);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 1;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = 1");
}

// Scenario: Computing the magnitude of vector(0, 1, 0)
// Given v ← vector(0, 1, 0)
// Then magnitude(v) = 1
void test_ch1_magnitude_of_unit_vector_y(void)
{
	printf("Chapter 1: Computing the magnitude of Y unit vector(0, 1, 0)\n");
	t_tuple	v = vector(0, 1, 0);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 1;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = 1");
}

// Scenario: Computing the magnitude of vector(0, 0, 1)
// Given v ← vector(0, 0, 1)
// Then magnitude(v) = 1
void test_ch1_magnitude_of_unit_vector_z(void)
{
	printf("Chapter 1: Computing the magnitude of Z unit vector(0, 0, 1)\n");
	t_tuple	v = vector(0, 0, 1);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 1;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = 1");
}

// Scenario: Computing the magnitude of vector(1, 2, 3)
// Given v ← vector(1, 2, 3)
// Then magnitude(v) = √14
void test_ch1_magnitude_of_vector1(void)
{
	printf("Chapter 1: Computing the magnitude of vector(1, 2, 3)\n");
	t_tuple	v = vector(1, 2, 3);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 3.741657387;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = √14");
}

// Scenario: Computing the magnitude of vector(-1, -2, -3)
// Given v ← vector(-1, -2, -3)
// Then magnitude(v) = √14
void test_ch1_magnitude_of_vector2(void)
{
	printf("Chapter 1: Computing the magnitude of vector(-1, -2, -3)\n");
	t_tuple	v = vector(-1, -2, -3);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 3.741657387;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = √14");
}

// Scenario: Normalizing vector(4, 0, 0) gives (1, 0, 0)
// Given v ← vector(4, 0, 0)
// Then normalize(v) = vector(1, 0, 0)
void	test_ch1_normalize_unit_vector(void)
{
	printf("Chapter 1: Normalizing vector(4, 0, 0) gives (1, 0, 0)\n");
	t_tuple	v = vector(4, 0, 0);
	t_tuple	normalized = normalize_vector(v);
	t_tuple	expected_vector = vector(1, 0, 0);
	TEST_ASSERT(tuples_equal(normalized, expected_vector), "normalize(v) = vector(1, 0, 0)");
}

// Scenario: Normalizing vector(1, 2, 3)
// Given v ← vector(1, 2, 3)
// # vector(1/√14, 2/√14, 3/√14)
// Then normalize(v) = approximately vector(0.26726, 0.53452, 0.80178)
void	test_ch1_normalize_vector(void)
{
	printf("Chapter 1: Normalizing vector(1, 2, 3)\n");
	t_tuple	v = vector(1, 2, 3);
	t_tuple	normalized = normalize_vector(v);
	double inv = 1.0 / sqrt(14.0);
	t_tuple expected_vector = vector(1.0*inv, 2.0*inv, 3.0*inv);
	// t_tuple	expected_vector = vector(0.26726, 0.53452, 0.80178);
	TEST_ASSERT(tuples_equal(normalized, expected_vector),
"approximately vector(1/sqrt14, 2/sqrt14, 3/sqrt14)");
	// TEST_ASSERT(tuples_equal(normalized, expected_vector), "approximately vector(0.26726, 0.53452, 0.80178)");
}

// Scenario: The magnitude of a normalized vector
// Given v ← vector(1, 2, 3)
// When norm ← normalize(v)
// Then magnitude(norm) = 1
void test_ch1_magnitude_of_normalized_vector(void)
{
	printf("Chapter 1: The magnitude of a normalized vector(1, 2, 3)\n");
	t_tuple	v = vector(1, 2, 3);
	t_tuple	norm = normalize_vector(v);
	// NOT THE SAME "v", BUT SAME "norm":
	// WILL WORK FOR ANY "v", EXCEPT "v(0,0,0)":
	// printf("v = %f %f %f\n", v.x, v.y, v.z);
	// printf("norm = %f %f %f\n", norm.x, norm.y, norm.z);
	double magnitude = magnitude_of_vector(norm);
	double expected_magnitude = 1;
	double inv = 1.0 / sqrt(14.0);
	t_tuple expected_vector = vector(1.0*inv, 2.0*inv, 3.0*inv);
	// t_tuple	expected_vector = vector(0.26726, 0.53452, 0.80178);
	TEST_ASSERT(tuples_equal(norm, expected_vector), "approximately vector(1/sqrt14, 2/sqrt14, 3/sqrt14)");
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(norm) = 1");
}


// Scenario: The dot product of two tuples
// Given a ← vector(1, 2, 3)
// And b ← vector(2, 3, 4)
// Then dot(a, b) = 20
void	test_ch1_dot_product_of_two_tuples(void)
{
	printf("Chapter 1: The dot product of two tuples\n");
	t_tuple	a = vector(1, 2, 3);
	t_tuple	b= vector(2, 3, 4);
	double	dot = dot_product(a, b);
	double	expected_dot = 20;
	TEST_ASSERT(floats_equal(dot, expected_dot), "dot(a, b) = 20");
}

// Scenario: The cross product of two vectors
// Given a ← vector(1, 2, 3)
// And b ← vector(2, 3, 4)
// Then cross(a, b) = vector(-1, 2, -1)
// And cross(b, a) = vector(1, -2, 1)
void	test_ch1_cross_product_of_two_vectors(void)
{
	printf("Chapter 1: The cross product of two vectors\n");
	t_tuple	a = vector(1, 2, 3);
	t_tuple	b = vector(2, 3, 4);

	t_tuple	cross_ab = cross_product(a, b);
	t_tuple	cross_ba = cross_product(b, a);
	t_tuple	expected_ab = vector(-1, 2, -1);
	t_tuple	expected_ba = vector(1, -2, 1);
	TEST_ASSERT(tuples_equal(cross_ab, expected_ab), "cross(a, b) = vector(-1, 2, -1)");
	TEST_ASSERT(tuples_equal(cross_ba, expected_ba), "cross(b, a) = vector(1, -2, 1)");
}

void	test_ch1_cross_product_of_axes_vectors(void)
{
	printf("Chapter 1: The cross product of axes \n 	x(1, 0, 0), y(0, 1, 0)\n");
	t_tuple	x = vector(1, 0, 0);
	t_tuple	y = vector(0, 1, 0);

	t_tuple	cross_xy = cross_product(x, y);
	t_tuple	cross_yx = cross_product(y, x);
	t_tuple	expected_xy = vector(0, 0, 1);
	t_tuple	expected_yx = vector(0, 0, -1);
	TEST_ASSERT(tuples_equal(cross_xy, expected_xy), "cross(x, y) = z_vector(0, 0, 1)");
	TEST_ASSERT(tuples_equal(cross_yx, expected_yx), "cross(y, x) = -z_vector(0, 0, -1)");
}

/// test_projectile.c my tests for "Putting it together" and tick() function:
void	test_ch1_test_normalize_velocity(void)
{
	printf("Chapter 1: My own test: Normalize_velocity\n");
	printf("vector(1, 3, 0)");
	t_tuple	v = vector(1, 3, 0);
	t_tuple	norm = normalize_vector(v);
	double	magnitude = magnitude_of_vector(norm);
	double expected_magnitude = 1.0;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), " = 1.0");
	printf("will be given as 2nd parameter to projectile_create\n");
}

void test_ch1_test_tick_updates_position_and_velocity(void) 
{
	// Инициализация снаряда с НОРМАЛИЗОВАННОЙ скоростью
	t_projectile p = projectile_create(point(0, 1, 0), vector(1, 1, 0));
	t_environment env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};

	p = tick(env, p);

/* Compute expected using exact math (no rounding literals) */
	double	inv = 1.0 / sqrt(2.0); /* normalized(1,1,0) */
	t_tuple	expected_pos = point(inv, 1.0 + inv, 0.0);
	t_tuple	expected_vel = vector(inv - 0.01, inv - 0.1, 0.0);
	TEST_ASSERT(tuples_equal(p.position, expected_pos),
			"Position after 1st tick should be (~inv, 1+inv, 0)");
	TEST_ASSERT(tuples_equal(p.velocity, expected_vel),
			"Velocity after 1st tick should be (~inv-0.01, ~inv-0.1, 0)");
	// TEST_ASSERT(tuples_equal(p.position, point(0.70711, 1.70711, 0)), 
	// 			"Position after 1st tick should be (0.707, 1.707, 0)");

	// TEST_ASSERT(tuples_equal(p.velocity, vector(0.69711, 0.60711, 0)), 
	// 			"Velocity after 1st tick should be (0.697, 0.607, 0)");
	printf("p.position :");
	print_tuple(p.position);
	printf("p.velocity :");
	print_tuple(p.velocity);
	printf("\n");
}

void	test_ch1_multiple_ticks(void) 
{
	t_projectile	p = projectile_create(point(0, 1, 0), vector(1, 1, 0));
	t_environment	env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};

	// Array of expected values for the first 4 ticks (0-3)
	double inv = 1.0 / sqrt(2.0);
	t_tuple expected_pos[] = {
		point(0.0, 1.0, 0.0),
		point(inv, 1.0 + inv, 0.0),
		point(inv + (inv - 0.01), 1.0 + inv + (inv - 0.1), 0.0),
		point(inv + (inv - 0.01) + (inv - 0.02),
		1.0 + inv + (inv - 0.1) + (inv - 0.2), 0.0)
	};
	t_tuple expected_vel[] = {
		vector(inv, inv, 0.0),
		vector(inv - 0.01, inv - 0.1, 0.0),
		vector(inv - 0.02, inv - 0.2, 0.0),
		vector(inv - 0.03, inv - 0.3, 0.0)
	};
	// t_tuple expected_pos[] = {
	// 	point(0.00000, 1.00000, 0),    // Tick 0 (initial state)
	// 	point(0.70711, 1.70711, 0),    // Tick 1
	// 	point(1.40422, 2.31422, 0),    // Tick 2
	// 	point(2.09133, 2.82133, 0)     // Tick 3
	// };

	// t_tuple expected_vel[] = {
	// 	vector(0.70711, 0.70711, 0),   // Tick 0 (initial velocity)
	// 	vector(0.69711, 0.60711, 0),   // Tick 1
	// 	vector(0.68711, 0.50711, 0),   // Tick 2
	// 	vector(0.67711, 0.40711, 0)    // Tick 3
	// };

	// Check initial state (tick 0)
	printf("=== Initial state (tick 0) ===\n");
	printf("Given position:		"); print_tuple(p.position);
	printf("Given velocity:		"); print_tuple(vector(1, 1, 0));
	printf("Normalized velocity:	"); print_tuple(p.velocity);
	TEST_ASSERT(tuples_equal(p.position, expected_pos[0]), "Initial position");
	TEST_ASSERT(tuples_equal(p.velocity, expected_vel[0]), "Initial velocity");

	// Apply tick() sequentially and verify results
	for (int i = 1; i <= 3; i++) 
	{
		p = tick(env, p);
		
		printf("\n=== After tick %d ===\n", i);
		printf("Expected position: "); print_tuple(expected_pos[i]);
		// printf("Actual position:   "); print_tuple(p.position);
		printf("Expected velocity: "); print_tuple(expected_vel[i]);
		// printf("Actual velocity:   "); print_tuple(p.velocity);
		
		TEST_ASSERT(tuples_equal(p.position, expected_pos[i]), 
					"Position after tick");
		TEST_ASSERT(tuples_equal(p.velocity, expected_vel[i]), 
					"Velocity after tick");
	}
}

void test_ch1_projectile_impact(void) 
{
	t_projectile p = projectile_create(point(0, 1, 0), vector(1, 1, 0));
	t_environment env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};
	int ticks = 0;
	int max_ticks = 50;

	printf("Launching projectile...\n");
	while (p.position.y > 0 && ticks < max_ticks)
	{
		p = tick(env, p);
		ticks++;
		printf("Tick %2d:	X = %.5f,	Y = %.5f,	Z = %.5f\n", ticks, p.position.x, p.position.y, p.position.z);
	}

	// Check Y ≤ 0
	TEST_ASSERT(p.position.y <= 0.0 + EPS, 
				"Projectile Y > 0 (actual Y)");

	// Check number of ticks (≈17)
	int expected_ticks = 17;
	TEST_ASSERT(floats_equal(ticks, expected_ticks), "Expected ticks:	");
	TEST_ASSERT(floats_equal(ticks, expected_ticks), "are equal");
	printf("= %d\n\n", expected_ticks);

	// Additional info on error
	if (!floats_equal(ticks, expected_ticks))
	{
		printf("Final position: ");
		print_tuple(p.position);
		printf("Velocity at impact: ");
		print_tuple(p.velocity);
	}
}

//TODO ON CANVAS:
// " Then, run tick repeatedly until the projectile’s y position is less than or equal
// to 0. Report the projectile’s position after each tick, and the number of ticks
// it takes for the projectile to hit the ground. Try multiplying the projectile’s
// initial velocity by larger and larger numbers to see how much farther the
// projectile goes! "

// --- Test functions from Chapter 2: colors, canvas ---

// Scenario: Colors are (red, green, blue) tuples
// Given c ← color(-0.5, 0.4, 1.7)
// Then c.red = -0.5
// And c.green = 0.4
// And c.blue = 1.7
// void	test_ch2_rgb_tuple_direct(void)
// {
// 	printf("Chapter 2: rgb(-0.5, 0.4, 1.7) direct values: 0 - 1\n\n");
// 	t_tuple color = rgb(-0.5, 0.4, 1.7);//color = vector
// 	TEST_ASSERT(floats_equal(color.x, -0.5), "RED color.x = -0.5");
// 	TEST_ASSERT(floats_equal(color.y, 0.4), "GREEN color.y = 0.4");
// 	TEST_ASSERT(floats_equal(color.z, 1.7), "BLUE color.z = 1.7");
// 	printf("\n");
// 	TEST_ASSERT(floats_equal(color.w, 0.0), "color.w = 0.0");
// 	TEST_ASSERT(is_point(color) == 0, "color is not a point");
// 	TEST_ASSERT(is_vector(color) == 1, "color a is a vector");
// 	printf("\n");
// 	print_tuple(color);
// 	printf("\n");
// }

void	test_ch2_rgb_tuple_direct(void)
{
	printf("Chapter 2: rgb(-0.5, 0.4, 1.7) direct values: 0 - 1\n\n");
	t_tuple my_color_value = rgb(-0.5, 0.4, 1.7);
	TEST_ASSERT(floats_equal(my_color_value.x, -0.5), "RED color.x = -0.5");
	TEST_ASSERT(floats_equal(my_color_value.y, 0.4), "GREEN color.y = 0.4");
	TEST_ASSERT(floats_equal(my_color_value.z, 1.7), "BLUE color.z = 1.7");
	printf("\n");
	TEST_ASSERT(floats_equal(my_color_value.w, 0.0), "color.w = 0.0");
	TEST_ASSERT(is_point(my_color_value) == 0, "color is not a point");
	TEST_ASSERT(is_vector(my_color_value) == 1, "color a is a vector");
	printf("\n");
	print_tuple(my_color_value);
	printf("\n");
}


// Scenario: Adding colors
// Given c1 ← color(0.9, 0.6, 0.75)
// And c2 ← color(0.7, 0.1, 0.25)
// Then c1 + c2 = color(1.6, 0.7, 1.0)
// test_ch1_add_two_tuples is the same
void test_ch2_add_colors(void)
{
	printf("Chapter 2: Adding two 'colors' = 'vectors'\n");
	t_tuple c1 = rgb(0.9, 0.6, 0.75);// = vector
	t_tuple c2 = rgb(0.7, 0.1, 0.25);// = vector
	t_tuple sum = add(c1, c2);
	t_tuple expected = vector(1.6, 0.7, 1.0);// = vector
	TEST_ASSERT(tuples_equal(expected, sum), "sum = rgb(1.6, 0.7, 1.0)");
}

// Scenario: Subtracting colors
// Given c1 ← color(0.9, 0.6, 0.75)
// And c2 ← color(0.7, 0.1, 0.25)
// Then c1 - c2 = color(0.2, 0.5, 0.5)
// same as test_ch1_substract_v_from_v()
void test_ch2_substract_colors(void)
{
	printf("Chapter 2: Substracting two colors(c1 - c2) 'colors' = 'vectors'\n");
	t_tuple c1 = vector(0.9, 0.6, 0.75);//left to emphasize 
	t_tuple c2 = rgb(0.7, 0.1, 0.25);
	t_tuple diff = substract_tuples(c1, c2);
	t_tuple expected_color = rgb(0.2, 0.5, 0.5);// = vector
	TEST_ASSERT(tuples_equal(expected_color, diff), "diff = rgb(0.2, 0.5, 0.5)");
}

// Scenario: Multiplying a color by a scalar
// Given c ← color(0.2, 0.3, 0.4)
// Then c * 2 = color(0.4, 0.6, 0.8)
void test_ch2_multiplying_a_color_by_a_scalar(void)
{
	printf("Chapter 2: Multiplying a color by a scalar 'colors' = 'vectors'\n");
	t_tuple	c = vector(0.2, 0.3, 0.4);//left to emphasize 
	double	scalar = 2;
	t_tuple	tproduct = multiply_tuple_scalar(c, scalar);
	t_tuple	expected_color = rgb(0.4, 0.6, 0.8);// = vector
	TEST_ASSERT(tuples_equal(tproduct, expected_color), "product = rgb(0.4, 0.6, 0.8)");
}
// Hadamard product (or Schur product)
// Scenario: Multiplying colors
// Given c1 ← color(1, 0.2, 0.4)
// And c2 ← color(0.9, 1, 0.1)
// Then c1 * c2 = color(0.9, 0.2, 0.04)
void test_ch2_multiplying_two_colors(void)
{
	printf("Chapter 2: Multiplying two 'colors' = 'vectors')\n");
	t_tuple	c1 = rgb(1, 0.2, 0.4); //color = vector
	t_tuple	c2 = vector(0.9, 1, 0.1); //left to emphasize 
	t_tuple	tproduct = multiply_tuples(c1, c2);
	t_tuple	expected_color = rgb(0.9, 0.2, 0.04);
	TEST_ASSERT(tuples_equal(tproduct, expected_color), "product = 'color' - rgb(0.9, 0.2, 0.04)");
}

// --- Chapter 2: canvas: ---

// Scenario: Creating a canvas ("image" for mlx compatibility)
// Given c ← canvas(10, 20)
// Then c.width = 10
// And c.height = 20
// And every pixel of c is color(0, 0, 0)
void test_ch2_creating_an_image(void)
{
	printf("Chapter 2: creating a 'canvas' = 'image')\n");
	void	*mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	t_image	*canvas = image_create(mlx, 10, 20);

		TEST_ASSERT(canvas, "canvas created");
		TEST_ASSERT(canvas->width == 10, "width = 10");
		TEST_ASSERT(canvas->height == 20, "height = 20");
	int x, y;
	int all_black = 1;
	for (y = 0; y < canvas->height && all_black; ++y)
	{
		for (x = 0; x < canvas->width; ++x)
		{
			unsigned int *pixel = (unsigned int *)(canvas->addr
				+ y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
			if (*pixel != 0x000000)
			{
				all_black = 0;
				break;
			}
		}
	}
	TEST_ASSERT(all_black, "all pixels are black (0x000000)");
	/*DESTROY PART:*/
	image_destroy(canvas);		// image_destroy only releases the image resources (img_ptr) and the t_image structure
	// MLX cleanup for Linux
	#ifdef __linux__
	mlx_destroy_display(mlx);  // Destroys X11 structures
	free(mlx);                 // Frees the mlx pointer
	#endif
}

// Scenario: Writing pixels to a canvas
// Given c ← canvas(10, 20)
// And red ← color(1, 0, 0)
// When write_pixel(c, 2, 3, red)
// Then pixel_at(c, 2, 3) = red
// Initiate MLX and create canvas
void test_ch2_writing_pixels(void) 
{
	printf("Chapter 2: writing pixels to 'canvas' = 'image'\n");
	// Initiate MLX and create canvas
	void *mlx = mlx_init();
	TEST_ASSERT(mlx, "mlx_init() success");
	t_image *canvas = image_create(mlx, 10, 20);
	TEST_ASSERT(canvas, "canvas created");

	// Create red 'color' = 'tuple' (RGBA)
	t_color red = {1.0, 0.0, 0.0, 1.0}; // Red = 255, G = 0, B = 0, A = 255
	t_color_format cf = { red, FORMAT_RGBA };
	// Write pixel
	write_pixel(canvas, 2, 3, cf);

	// Check pixel
	t_color pixel_color = read_pixel(canvas, 2, 3);
	print_color(pixel_color);
	printf("\n");

	unsigned int pixel = color_to_mlx(&pixel_color, FORMAT_RGBA);
	printf("red pixel : 0x%08X\n", pixel);
	TEST_ASSERT(pixel == 0xFF0000FF, "Pixel (2,3) is red");

	// Clean up
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}
/*
| Format | Hex Value   | Explanation                          |
|--------|-------------|--------------------------------------|
| RGBA   | 0xFF0000FF  | Red, Green, Blue, Alpha			  |
| ARGB   | 0xFFFF0000  | Alpha, Red, Green, Blue			  |
| BGRA   | 0x0000FFFF  | Blue, Green, Red, Alpha			  |
| ABGR   | 0xFF0000FF  | Alpha, Blue, Green, Red			  |
*/

// TO BE DONE:
// Scenario: Constructing the PPM header
// Given c ← canvas(5, 3)
// When ppm ← canvas_to_ppm(c)
void test_ch2_constructing_ppm_header(void)
{
	printf("Chapter 2: Constructing the PPM header)\n");
	void	*mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	t_image	*canvas = image_create(mlx, 5, 3);

		TEST_ASSERT(canvas, "canvas created");
		TEST_ASSERT(canvas->width == 5, "width = 5");
		TEST_ASSERT(canvas->height == 3, "height = 3");
	int x, y;
	int all_black = 1;
	for (y = 0; y < canvas->height && all_black; ++y)
	{
		for (x = 0; x < canvas->width; ++x)
		{
			unsigned int *pixel = (unsigned int *)(canvas->addr
				+ y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
			if (*pixel != 0x000000)
			{
				all_black = 0;
				break;
			}
		}
	}
	TEST_ASSERT(all_black, "all pixels are black (0x000000)");
	image_to_ppm(canvas, 1);

	// NECCESSARY DESTROY PART:
	image_destroy(canvas);		// image_destroy only releases the image resources (img_ptr) and the t_image structure
	// MLX cleanup for Linux
	#ifdef __linux__
	mlx_destroy_display(mlx);  // Destroys X11 structures
	free(mlx);                 // Frees the mlx pointer
	#endif
}

int	compare_files(const char *f1, const char *f2)
{
	FILE	*file1 = fopen(f1, "r");
	FILE	*file2 = fopen(f2, "r");
	int		c1, c2;

	if (!file1 || !file2)
		return (0);
	while (1)
	{
		c1 = fgetc(file1);
		c2 = fgetc(file2);
		if (c1 != c2)
		{
			fclose(file1);
			fclose(file2);
			return (0);
		}
		if (c1 == EOF)
			break;
	}
	fclose(file1);
	fclose(file2);
	return (1);
}


// Scenario: Constructing the PPM pixel data
// Given c ← canvas(5, 3)
// And c1 ← color(1.5, 0, 0)
// And c2 ← color(0, 0.5, 0)
// And c3 ← color(-0.5, 0, 1)
// When write_pixel(c, 0, 0, c1)
// And write_pixel(c, 2, 1, c2)
// And write_pixel(c, 4, 2, c3)
// And ppm ← canvas_to_ppm(c)
// Then lines 4-6 of ppm are
// """
// 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255
// """

//AUTOMISED is_canvas_black() ADDED:

static int	is_canvas_black(t_image *canvas)
{
	int	x;
	int	y;
	unsigned int	*pixel;
	
	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			pixel = (unsigned int *)(canvas->addr
				+ y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
				if (*pixel != 0x000000)
				return (0);
				x++;
			}
			y++;
		}
		return (1);
	}

void	test_ch2_constructing_the_ppm_pixel_data(void)
{
	void	*mlx;
	t_image	*canvas;
	t_color	c1, c2, c3;
	t_color_format cf1, cf2, cf3;
	int		fd;

	printf("Chapter 2: Constructing the PPM pixel data)\n");
	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	canvas = image_create(mlx, 5, 3);
	TEST_ASSERT(canvas, "canvas created");
	TEST_ASSERT(canvas->width == 5, "width = 5");
	TEST_ASSERT(canvas->height == 3, "height = 3");
	TEST_ASSERT(is_canvas_black(canvas), "all pixels are black (0x000000)");
	printf("\n");
	c1 = (t_color){1.5, 0.0, 0.0, 1.0};
	c2 = (t_color){0.0, 0.5, 0.0, 1.0};
	c3 = (t_color){-0.5, 0.0, 1.0, 1.0};
	cf1 = (t_color_format){c1, FORMAT_RGBA};
	cf2 = (t_color_format){c2, FORMAT_RGBA};
	cf3 = (t_color_format){c3, FORMAT_RGBA};
	write_pixel(canvas, 0, 0, cf1);
	write_pixel(canvas, 2, 1, cf2);
	write_pixel(canvas, 4, 2, cf3);

	// --- automization of comparisson ---
	fd = open("test_files/test_output.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		image_destroy(canvas);
		#ifdef __linux__
		mlx_destroy_display(mlx);
		free(mlx);
		#endif
		return;
	}
	image_to_ppm(canvas, fd);
	close(fd);

	TEST_ASSERT(compare_files("test_files/test_output.ppm", "test_files/expected.ppm"), "PPM matches reference look at test_files/");
	// --- end of automization ---
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

// Scenario: Splitting long lines in PPM files
// Given c ← canvas(10, 2)
// When every pixel of c is set to color(1, 0.8, 0.6)
// And ppm ← canvas_to_ppm(c)
// Then lines 4-7 of ppm are
// """
// 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
// 153 255 204 153 255 204 153 255 204 153 255 204 153
// 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
// 153 255 204 153 255 204 153 255 204 153 255 204 153
// """
void	test_ch2_splitting_long_lines(void)
{
	void	*mlx;
	t_image	*canvas;
	t_color	c;
	t_color_format cf;
	int		fd;

	printf("Chapter 2: Splitting long lines in PPM files)\n");
	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	canvas = image_create(mlx, 10, 2);
	TEST_ASSERT(canvas, "canvas created");
	TEST_ASSERT(canvas->width == 10, "width = 10");
	TEST_ASSERT(canvas->height == 2, "height = 2");
	TEST_ASSERT(is_canvas_black(canvas), "all pixels are black (0x000000)");
	printf("\n");
	c = (t_color){1.0, 0.8, 0.6, 1.0};
	cf = (t_color_format){c, FORMAT_RGBA};
	int x, y;

	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			write_pixel(canvas, x, y, cf);
			x++;
		}
		y++;
	}

	// --- automization of comparisson ---
	fd = open("test_files/splitting_long_output.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		image_destroy(canvas);
		#ifdef __linux__
		mlx_destroy_display(mlx);
		free(mlx);
		#endif
		return;
	}
	image_to_ppm(canvas, fd);
	close(fd);

	TEST_ASSERT(compare_files("test_files/splitting_long_output.ppm", "test_files/splitting_long.ppm"), "PPM matches reference look at test_files/");
	// --- end of automization ---
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

static bool	file_ends_with_newline(const char *filename)
{
	FILE *fp = fopen(filename, "rb");
	int last_char = 0;
	if (!fp)
		return false;
	if (fseek(fp, -1, SEEK_END) != 0) {
		fclose(fp);
		return false; // файл пустой или ошибка
	}
	last_char = fgetc(fp);
	fclose(fp);
	return last_char == '\n';
}

// Scenario: PPM files are terminated by a newline character
// Given c ← canvas(5, 3)
// When ppm ← canvas_to_ppm(c)
// Then ppm ends with a newline character
// That’s really all there is to PPM files. The next step 
void	test_ch2_newline_character_at_the_end(void)
{
	void	*mlx;
	t_image	*canvas;
	int		fd;

	printf("Chapter 2: PPM files are terminated by a newline character)\n");
	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed!\n");
		return ;
	}
	canvas = image_create(mlx, 5, 3);
	fd = open("test_files/new_line_end_output.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
	{
		perror("open");
		image_destroy(canvas);
		#ifdef __linux__
		mlx_destroy_display(mlx);
		free(mlx);
		#endif
		return;
	}
	image_to_ppm(canvas, fd);
	close(fd);
	TEST_ASSERT(file_ends_with_newline("test_files/new_line_end_output.ppm"), "PPM ends with a newline character");
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	free(mlx);
	#endif
}

// HELPING FUNCTION:
// Scenario: Drawing a 3x3 pixel block around a point
// Given canvas ← canvas(5, 5)
// When draw_3x3_pixel_block(canvas, 2, 2, color(1, 0, 0))
// Then pixels at (1, 1), (1, 2), (1, 3), (2, 1), (2, 2), (2, 3), (3, 1), (3, 2), (3, 3) are red

// Рисуем область 3x3 вокруг точки (canvas_x, canvas_y) без for
void draw_3x3_pixel_block(t_image *canvas, int canvas_x, int canvas_y, int color)
{
    int px, py;

    // Центральный пиксель
    if (canvas_x >= 0 && canvas_x < canvas->width && canvas_y >= 0 && canvas_y < canvas->height)
        image_put_pixel(canvas, canvas_x, canvas_y, color);

    // Вверх
    py = canvas_y - 1;
    if (py >= 0 && py < canvas->height)
    {
        if (canvas_x >= 0 && canvas_x < canvas->width)
            image_put_pixel(canvas, canvas_x, py, color);
        px = canvas_x - 1;
        if (px >= 0 && px < canvas->width)
            image_put_pixel(canvas, px, py, color);
        px = canvas_x + 1;
        if (px >= 0 && px < canvas->width)
            image_put_pixel(canvas, px, py, color);
    }

    // Вниз
    py = canvas_y + 1;
    if (py >= 0 && py < canvas->height)
    {
        if (canvas_x >= 0 && canvas_x < canvas->width)
            image_put_pixel(canvas, canvas_x, py, color);
        px = canvas_x - 1;
        if (px >= 0 && px < canvas->width)
            image_put_pixel(canvas, px, py, color);
        px = canvas_x + 1;
        if (px >= 0 && px < canvas->width)
            image_put_pixel(canvas, px, py, color);
    }

    // Слева и справа от центра
    px = canvas_x - 1;
    if (px >= 0 && px < canvas->width && canvas_y >= 0 && canvas_y < canvas->height)
        image_put_pixel(canvas, px, canvas_y, color);
    px = canvas_x + 1;
    if (px >= 0 && px < canvas->width && canvas_y >= 0 && canvas_y < canvas->height)
        image_put_pixel(canvas, px, canvas_y, color);
}

void	test_ch2_test_projectile_trajectory(void)
{
	// Инициализация MLX и холста
	void *mlx = mlx_init();
	t_image *canvas = image_create(mlx, 300, 200);
	if (!canvas)
	{
		perror("Failed to create canvas");
		exit(1);
	}
	t_color red = {1.0, 0.0, 0.0, 1.0};
	int mlx_color = color_to_mlx(&red, FORMAT_RGBA);

	printf("Chapter 2: Projectile trajectory test\n");
	// FROM: test_ch1_projectile_impact
	t_projectile	p = projectile_create(point(0, 1, 0), vector(68, 120, 0));
	t_environment	env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};
	int ticks = 0;
	int max_ticks = 50;

	printf("Launching projectile...\n");
	float scale = 34.0; // Масштабирование для отображения на холсте
	while (p.position.y > 0 && ticks < max_ticks)
	{
		// Преобразование координат (мир -> холст) с масштабированием
		int canvas_x = (int)round(p.position.x * scale);
		int canvas_y = canvas->height - (int)round(p.position.y * scale);

		// Проверка границ FROM image_put_pixel
		if (canvas_x >= 0 && canvas_x < canvas->width && 
			canvas_y >= 0 && canvas_y < canvas->height) 
		{
			// Используем функцию отрисовки пикселя
			image_put_pixel(canvas, canvas_x, canvas_y, mlx_color);
			draw_3x3_pixel_block(canvas, canvas_x, canvas_y, mlx_color);
		}
		// USING: tick() функция обновления снаряда
		p = tick(env, p);
		ticks++;
		// Логирование FROM: test_ch1_projectile_impact
		printf("Tick %2d: X = %.5f, Y = %.5f\n", ticks, p.position.x, p.position.y);

	}
	// Сохранение в PPM (используем вашу функцию)
	int fd = open("test_files/trajectory14.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror("Error opening PPM file");
	} else {
		image_to_ppm(canvas, fd);
		close(fd);
	}
	printf("Projectile trajectory saved to test_files/trajectory14.ppm\n");

	// Очистка ресурсов
	image_destroy(canvas);
	#ifdef __linux__
	mlx_destroy_display(mlx);
	#endif
	free(mlx);
}

// Используемые функции:
// projectile_create() - ваша функция создания снаряда
// tick() - ваша функция обновления положения
// image_put_pixel() - ваша функция отрисовки пикселя
// image_to_ppm() - ваша функция сохранения PPM

// Особенности реализации:
// Инверсия Y: canvas_y = height - world_y (преобразование координат)
// Область 3x3: Для видимости точек рисуем не один пиксель, а блок 3x3
// Логирование: Сохраняем ваш вывод координат в консоль


// Scenario: Constructing and inspecting a 4x4 matrix
// Given the following 4x4 matrix M:
// | 1 | 2 | 3 | 4 |
// | 5.5 | 6.5 | 7.5 | 8.5 |
// | 9 | 10 | 11 | 12 |
// | 13.5 | 14.5 | 15.5 | 16.5 |
// Then M[0,0] = 1
// And M[0,3] = 4
// And M[1,0] = 5.5
// And M[1,2] = 7.5
// And M[2,2] = 11
// And M[3,0] = 13.5
// And M[3,2] = 15.5

void test_ch3_matrix_construction()
{
	printf("Chapter 3: Constructing and inspecting a 4x4 matrix)\n");
	double values[4][4] = {
		{1, 2, 3, 4},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5}
	};

	t_matrix M = create_matrix(values);

	// Проверки согласно тесту
	TEST_ASSERT((get_matrix_element(&M, 0, 0) == 1), "M[0,0] = 1");
	// assert(get_matrix_element(&M, 0, 0) == 1);
	TEST_ASSERT((get_matrix_element(&M, 0, 3) == 4), "M[0,3] = 4");
	// assert(get_matrix_element(&M, 0, 3) == 4);
	TEST_ASSERT((get_matrix_element(&M, 1, 0) == 5.5), "M[1,0] = 5.5");
	// assert(get_matrix_element(&M, 1, 0) == 5.5);
	TEST_ASSERT((get_matrix_element(&M, 1, 2) == 7.5), "M[1,2] = 7.5");
	// assert(get_matrix_element(&M, 1, 2) == 7.5);
	TEST_ASSERT((get_matrix_element(&M, 2, 2) == 11), "M[2,2] = 11");
	// assert(get_matrix_element(&M, 2, 2) == 11);
	TEST_ASSERT((get_matrix_element(&M, 3, 0) == 13.5), "M[3,0] = 13.5");
	// assert(get_matrix_element(&M, 3, 0) == 13.5);
	TEST_ASSERT((get_matrix_element(&M, 3, 2) == 15.5), "M[3,2] = 15.5");
	// assert(get_matrix_element(&M, 3, 2) == 15.5);
}

void test_ch3_identity_shape(void)
{
	printf("Chapter 3: Identity matrix shape (diagonal ones)\n");

	t_matrix	id;
	int			i;
	int			j;

	id = mat_identity(); /* build identity matrix*/
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (j == i)
			{
				TEST_ASSERT(floats_equal(id.data[i][j], 1.0), "Diagonal element is equal 1.0");
			}
			else
			{
				TEST_ASSERT(floats_equal(id.data[i][j], 0.0), "Off-diagonal element is equal 0.0");
			}
			j++;
		}
		i++;
	}
	print_matrix(id);
}

void test_ch3_matrix_equality(void)
{
	printf("Chapter 3: Matrix equality\n");
	t_matrix a;
	t_matrix b;

	// Initialize matrix A
	a.data[0][0] = 1; a.data[0][1] = 2; a.data[0][2] = 3; a.data[0][3] = 4;
	a.data[1][0] = 5; a.data[1][1] = 6; a.data[1][2] = 7; a.data[1][3] = 8;
	a.data[2][0] = 9; a.data[2][1] = 8; a.data[2][2] = 7; a.data[2][3] = 6;
	a.data[3][0] = 5; a.data[3][1] = 4; a.data[3][2] = 3; a.data[3][3] = 2;

	// Initialize matrix B (identical to A)
	b.data[0][0] = 1; b.data[0][1] = 2; b.data[0][2] = 3; b.data[0][3] = 4;
	b.data[1][0] = 5; b.data[1][1] = 6; b.data[1][2] = 7; b.data[1][3] = 8;
	b.data[2][0] = 9; b.data[2][1] = 8; b.data[2][2] = 7; b.data[2][3] = 6;
	b.data[3][0] = 5; b.data[3][1] = 4; b.data[3][2] = 3; b.data[3][3] = 2;

	// Test 1: Identical matrices should be equal
	TEST_ASSERT(mat_equal(a, b), "Matrices are equal");
	print_matrix(a);
	print_matrix(b);

	// Modify matrix B to make it different
	b.data[0][0] = 2; b.data[0][1] = 3; b.data[0][2] = 4; b.data[0][3] = 5;
	b.data[1][0] = 6; b.data[1][1] = 7; b.data[1][2] = 8; b.data[1][3] = 9;
	b.data[2][0] = 8; b.data[2][1] = 7; b.data[2][2] = 6; b.data[2][3] = 5;
	b.data[3][0] = 4; b.data[3][1] = 3; b.data[3][2] = 2; b.data[3][3] = 1;

	// Test 2: Different matrices should not be equal
	TEST_ASSERT(!mat_equal(a, b), "Matrices are not equal");
	print_matrix(a);
	print_matrix(b);
	printf("\n");
}

/*
*   run_mat_mul_test: Initializes matrices, runs mat_mul,
*   and checks the result against the expected output from the book.
*   Uses existing `print_matrix` and custom `mat_equal` functions.
*/
void	test_ch3_run_mat_mul_test(void)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	result;
	t_matrix	expected;

	// Initialize matrices A and B (data from "The Raytracer Challenge", p. 28)
	a = (t_matrix){{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}};
	b = (t_matrix){{{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}}};
	
	// Expected result for C = A * B
	expected = (t_matrix){{{20, 22, 50, 48}, {44, 54, 114, 108}, \
		{40, 58, 110, 102}, {16, 26, 46, 42}}};
	
	printf("Chapter 3: Testing matrice multiplication \n");
	printf("Matrix A:\n");
	print_matrix(a);
	printf("\nMatrix B:\n");
	print_matrix(b);

	result = mat_mul(a, b);

	printf("\nResult of A * B:\n");
	print_matrix(result);
	printf("\nExpected result:\n");
	print_matrix(expected);
	if (mat_equal(result, expected))
		printf("\nTest PASSED!\n");
	else
		printf("\nTest FAILED!\n");
}

void	test_ch3_multiply_matrix_by_tuple(void)
{
	printf("Chapter 3: Multiplying a matrix by a tuple \n\n");

	t_matrix	a;
	t_tuple		b;
	t_tuple		expected;
	t_tuple		result;

	// 1. Arrange
	a = (t_matrix){{{1, 2, 3, 4},
	{2, 4, 4, 2},
	{8, 6, 4, 1},
	{0, 0, 0, 1}}};

	printf("Matrix a:\n");
	print_matrix(a);

	b = (t_tuple){1, 2, 3, 1};
	printf("Tuple b:\n");
	print_tuple(b);
	printf("\n");

	expected = (t_tuple){18, 24, 33, 1};
	printf("Expected tuple:\n");
	print_tuple(expected);
	printf("\n");
	// 2. Act
	result = mat_mul_tuple(a, b);

	TEST_ASSERT(tuples_equal(expected, result), "a * b = tuple(18, 24, 33, 1)");
	printf("\n");
}

void	test_ch3_transpose_matrix(void)
{
	double	values[4][4] = {
		{0, 9, 3, 0},
		{9, 8, 0, 8},
		{1, 8, 5, 3},
		{0, 0, 5, 8}
	};
	double	expected_values[4][4] = {
		{0, 9, 1, 0},
		{9, 8, 8, 0},
		{3, 0, 5, 5},
		{0, 8, 3, 8}
	};
	t_matrix	a;
	t_matrix	expected;
	t_matrix	result;

	printf("Chapter 3: Transposing a matrix\n\n");

	a = create_matrix(values);
	expected = create_matrix(expected_values);

	printf("Matrix a (input):\n");
	print_matrix(a);

	result = mat_transpose(a);

	printf("\nMatrix result (transposed):\n");
	print_matrix(result);

	TEST_ASSERT(mat_equal(result, expected), "mat_transpose: transpose is correct");
}

/*
** Example: test_ch3_transpose_identity()
** Description: Unit test for transpose of the identity matrix.
** Uses: mat_identity(), mat_transpose(), mat_equal()
** Verified: All 42 Norm, naming, and formatting rules applied.
*/

void	test_ch3_transpose_identity(void)
{
	printf("Chapter 3: Transposing the identity matrix\n\n");
	const t_matrix	identity = mat_identity();
	t_matrix		result;
	printf("identity:\n");
	print_matrix(identity);
	result = mat_transpose(identity);
	printf("result:\n");
	print_matrix(result);
	TEST_ASSERT(mat_equal(result, identity), "transposed the identity matrix");
}

/*
Here begin tests using submatrice, determinant for inversing using recursion,
I am on my way with understanding it :)
*/

/*
** Example: test_ch3_determinant_2x2()
** Description: Unit test for the determinant of a 2x2 matrix.
** Uses: create_matrix(), mat_determinant()
** Verified: All 42 Norm, naming, and formatting rules applied.
 * This test handles 2x2 matrices standalone for isolation.
 * In recursion, 2x2 det works via zero-padding recognition in 4x4.
 * Main project lacks explicit 2x2 creation, so we use padding here.
 */
void test_ch3_determinant_2x2(void)
{
	printf("Chapter 3: Calculating the determinant of a 2x2 matrix\n\n");
	printf("This test handles 2x2 matrices standalone for isolation \n\n In recursion, 2x2 det works via zero-padding recognition in 4x4\n\n");

	// Create "2x2" as an array (not t_matrix)
	double values[2][2] = {{1, 5}, {-3, 2}};

	// Call det_2x2 directly (your static function, make it visible or copy the logic)
	double det = values[0][0] * values[1][1] - values[0][1] * values[1][0];  // Basic formula

	// Printing (adapt print_matrix for 2x2 if needed)
	printf("Matrix A (2x2):\n| %.4f %.4f |\n| %.4f %.4f |\n", values[0][0], values[0][1], values[1][0], values[1][1]);
	printf("\n");
	printf("Matrix determinant is: %f\n\n", det);

	TEST_ASSERT(floats_equal(det, 17.0), "Determinant of 2x2 matrix is correct and equal to:");
	printf("%f\n", det);
}


/*
** Example: test_ch3_submatrix_minor_cofactor()
** Description: Unit tests for submatrix, minor, and cofactor calculations.
** Uses: create_matrix(), mat_submatrix(), mat_minor(), mat_cofactor(), mat_equal()
*/
void	test_ch3_submatrix_minor_cofactor(void)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	sub;
	t_matrix	expected_sub;
	double  	a_values[4][4] = {
		{1, 5, 0, 0}, {-3, 2, 7, 0}, {0, 6, -3, 0}, {0, 0, 0, 0}
	};
	double      expected_sub_values[4][4] = {
		{-3, 7, 0, 0}, {0, -3, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}
	};

	printf("Chapter 3: Submatrix, Minor, and Cofactor\n\n");
	a = create_matrix(a_values);
	expected_sub = create_matrix(expected_sub_values);
	printf("test a matrix (initial):\n");
	print_matrix(a);
	printf("expected_sub matrix:\n");
	print_matrix(expected_sub);
	printf("Original 3x3 Matrix a:\n");
	print_matrix(a);

	// Test submatrix of a 3x3 matrix
	sub = mat_submatrix(a, 0, 1);
	printf("Submatrix of a (removing row 0, col 1):\n");
	print_matrix(sub);
	TEST_ASSERT(mat_equal(sub, expected_sub), "Submatrix of 3x3 is correct");

	// Test minor and cofactor
	b = create_matrix(a_values);
	// minor(A, 0, 0) is determinant of | 2,  7 | = 2*(-3) - 7*6 = -6 - 42 = -48
	//                                  | 6, -3 |
	TEST_ASSERT(floats_equal(mat_minor(b, 0, 0), -48), "Minor of 3x3 matrix");
	// cofactor(A, 0, 0) is the same, since (0+0) is even.
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 0), -48), "Cofactor (sign not changed)");

	// minor(A, 1, 0) is determinant of | 5,  0 | = 5*(-3) - 0*6 = -15
	//                                  | 6, -3 |
	TEST_ASSERT(floats_equal(mat_minor(b, 1, 0), -15), "Minor of 3x3 matrix (case 2)");
	// cofactor(A, 1, 0) is negated, since (1+0) is odd.
	TEST_ASSERT(floats_equal(mat_cofactor(b, 1, 0), 15), "Cofactor (sign changed)");
}

/*
** Example: test_ch3_determinant_3x3_and_4x4()
** Description: Unit tests for 3x3 and 4x4 matrix determinants.
** Uses: create_matrix(), mat_determinant(), mat_cofactor()
*/
void	test_ch3_determinant_3x3_and_4x4(void)
{
	t_matrix	a;
	t_matrix	b;
	double		a_values[4][4] = {
		{1, 2, 6, 0}, {-5, 8, -4, 0}, {2, 6, 4, 0}, {0, 0, 0, 0}
	};
	double		b_values[4][4] = {
		{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}
	};

	printf("Chapter 3: Calculating determinants of 3x3 and 4x4 matrices\n\n");

	// Test 3x3 determinant
	a = create_matrix(a_values);
	printf("Matrix A (3x3):\n");
	print_matrix(a);
	TEST_ASSERT(floats_equal(mat_cofactor(a, 0, 0), 56),   "Cofactor A(0,0) = 56");
	TEST_ASSERT(floats_equal(mat_cofactor(a, 0, 1), 12),   "Cofactor A(0,1) = 12");
	TEST_ASSERT(floats_equal(mat_cofactor(a, 0, 2), -46),  "Cofactor A(0,2) = -46");
	// Expected: 1*56 + 2*12 + 6*(-46) = 56 + 24 - 276 = -196
	TEST_ASSERT(floats_equal(mat_determinant(a), -196), "Determinant of 3x3 matrix");
	printf(ANSI_COLOR_RED "Matrix a determinant is \n" \
		"Cofactor A(0,0)*A(0,0)\n" \
		" + \n" \
		"Cofactor A(0,1)*A(0,1)\n" \
		" + \n" \
		"Cofactor A(0,2)*A(0,2)\n" \
		"_______________________\n" \
		":\n%f\n\n" ANSI_COLOR_RESET, mat_determinant(a));
	// Test 4x4 determinant
	b = create_matrix(b_values);
	printf("\nMatrix B (4x4):\n");
	print_matrix(b);
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 0), 690),  "Cofactor B(0,0) = 690");
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 1), 447),  "Cofactor B(0,1) = 447");
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 2), 210),  "Cofactor B(0,2) = 210");
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 3), 51),   "Cofactor B(0,3) = 51");
	// Expected: -2*690 + (-8)*447 + 3*210 + 5*51 = -1380 - 3576 + 630 + 255 = -4071
	TEST_ASSERT(floats_equal(mat_determinant(b), -4071), "Determinant of 4x4 matrix");
	printf(ANSI_COLOR_RED "Matrix determinant is:\n%f\n\n" ANSI_COLOR_RESET, mat_determinant(b) );
}

/*
** Example: test_ch3_inversion()
** Description: Unit tests for matrix inversion, checking for invertibility.
** Uses: create_matrix(), mat_inverse(), mat_determinant(), mat_equal()
** Verified: All 42 Norm, naming, and formatting rules applied.
*/
void    test_ch3_inversion(void)
{
	t_matrix    a;
	t_matrix    inv_a;
	t_matrix    expected_inv;
	bool        is_invertible;
	double      a_values[4][4] = {
		{-5 , 2 , 6 , -8},
		{1 , -5 , 1 , 8},
		{7 , 7 , -6 , -7},
		{1 , -3 , 7 , 4}
	};
	// double      a_to_invert[4][4] = {
	// 	{-5 , 2 , 6 , -8},
	// 	{1 , -5 , 1 , 8},
	// 	{7 , 7 , -6 , -7},
	// 	{1 , -3 , 7 , 4}
	// };

	double      expected_values[4][4] = {
		{0.21805 , 0.45113 , 0.24060 , -0.04511},
		{-0.80827 , -1.45677 , -0.44361 , 0.52068},
		{-0.07895 , -0.22368 , -0.05263 , 0.19737},
		{-0.52256 , -0.81391 , -0.30075 , 0.30639}
	};

	printf("Chapter 3: Matrix Inversion\n\n");
	a = create_matrix(a_values);
	expected_inv = create_matrix(expected_values);
	printf("Matrix A:\n");
	print_matrix(a);

	// Test invertibility
	TEST_ASSERT(!floats_equal(mat_determinant(a), 0), "Matrix is invertible (det != 0)");

	inv_a = mat_inverse(a, &is_invertible);
	TEST_ASSERT(is_invertible, "mat_inverse reports success");

	printf("Inverse of A (calculated):\n");
	print_matrix(inv_a);
	printf("Inverse of A (expected):\n");
	print_matrix(expected_inv);

	TEST_ASSERT(mat_equal(inv_a, expected_inv), "Calculated inverse matches expected inverse");
}

/*
** Example: test_ch3_inverse_sanity_check()
** Description: Sanity check: A * inverse(A) must be the identity matrix.
** Uses: mat_mul(), mat_inverse(), mat_identity(), mat_equal()
*/
void	test_ch3_inverse_sanity_check(void)
{
	t_matrix    a;
	t_matrix    inv_a;
	t_matrix    product;
	bool        ok;
	double      a_values[4][4] = {
		{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}
	};

	printf("Chapter 3: Sanity Check: A * inverse(A) = Identity\n\n");
	a = create_matrix(a_values);
	printf("Matrix A:\n");
	print_matrix(a);

	inv_a = mat_inverse(a, &ok);
	TEST_ASSERT(ok, "Matrix A is invertible for sanity check");
	printf("Inverse of A:\n");
	print_matrix(inv_a);

	product = mat_mul(a, inv_a);
	printf("Product of A * inverse(A):\n");
	print_matrix(product);

	// The product should be the identity matrix
	TEST_ASSERT(mat_equal(product, mat_identity()), "Product of matrix and its inverse is identity");
}

/*
** Example: test_ch4_translation()
** Description: Tests for the translation matrix.
** Uses: translation(), point(), vector(), mat_mul_tuple(), tuples_equal()
** Verified: Based on Chapter 4 of "The Raytracer Challenge".
*/

t_matrix	translation(double x, double y, double z)
{
	t_matrix	m;

	m = mat_identity();
	m.data[0][3] = x;
	m.data[1][3] = y;
	m.data[2][3] = z;
	return (m);
}

/*
** Example: test_ch4_translation_moves_point()
** Description: Unit test for applying a translation matrix to a point.
** Uses: translation(), point(), mat_mul_tuple(), tuples_equal()
** Verified: Based on "The Raytracer Challenge", Chapter 4.
*/
void	test_ch4_translation_moves_point(void)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result_p;
	t_tuple		expected_p;

	printf("Chapter 4: Multiplying a point by a translation matrix\n");
	
	// Arrange: Create translation matrix and point
	transform = translation(5, -3, 2);
	p = point(-3, 4, 5);
	expected_p = point(2, 1, 7);

	// Act: Apply the transformation
	result_p = mat_mul_tuple(transform, p);

	// Assert: Check if the point was moved correctly
	printf("%-20s", "Original matrix:");
	print_matrix(transform);
	printf("%-20s", "Original point:");
	print_tuple(p);
	printf("%-20s", "Transformed point:");
	print_tuple(result_p);
	TEST_ASSERT(tuples_equal(result_p, expected_p), "Point should be translated to (2, 1, 7)");
	printf("\n");
}

/*
** Example: test_ch4_inverse_translation_moves_point_back()
** Description: Unit test for applying an inverse translation matrix.
** Uses: translation(), mat_inverse(), point(), mat_mul_tuple(), tuples_equal()
** Verified: Based on "The Raytracer Challenge", Chapter 4.
*/
// void	test_ch4_inverse_translation_moves_point_back(void)
// {
// 	t_matrix	transform;
// 	t_matrix	inv_transform;
// 	t_tuple		p;
// 	t_tuple		translated_p;
// 	// t_tuple		original_p;
// 	bool		ok;

// 	printf("Chapter 4: Multiplying a point by the inverse of a translation matrix\n");

// 	// Arrange: Create translation matrix, its inverse, and a point
// 	transform = translation(5, -3, 2);
// 	printf("%-20s", "Matrix translation(5, -3, 2):\n");
// 	print_matrix(transform);
// 	printf("\n");

// 	inv_transform = mat_inverse(transform, &ok);
// 	printf("%-20s", "Matrix mat_inverse(transform):\n");
// 	print_matrix(inv_transform);
// 	printf("\n");

// 	p = point(-3, 4, 5);
// 	printf("%-20s", "p point(-3, 4, 5):\n");
// 	print_tuple(p);
// 	printf("\n");

// 	translated_p = mat_mul_tuple(inv_transform, p);
// 	printf("%-20s", "inv * p = point(-8, 7, 3):\n");
// 	print_tuple(translated_p);
// 	printf("\n");

// 	// Act: Apply the inverse transformation
// 	// original_p = mat_mul_tuple(inv_transform, translated_p);

// 	// Assert: Check if the point is back to its original coordinates
// 	// printf("%-20s", "Inverse matrix:");
// 	// print_matrix(inv_transform);
// 	// printf("%-20s", "Translated point:");
// 	// print_tuple(translated_p);
// 	// printf("%-20s", "Moved-back point:");
// 	// print_tuple(original_p);
// 	TEST_ASSERT(tuples_equal(translated_p, point(-8, 7, 3)), "Point should return to original position");
// 	printf("\n");
// }

/*
** Example: test_ch4_inverse_translation_moves_point_back()
** Description: Unit test for applying an inverse translation matrix
**              to return a point to its original position.
** Uses: translation(), mat_inverse(), point(), mat_mul_tuple(), tuples_equal()
** Verified: Based on "The Raytracer Challenge", Chapter 4.
*/
void	test_ch4_inverse_translation_moves_point_back(void)
{
	t_matrix	transform;
	t_matrix	inv_transform;
	t_tuple		p;
	t_tuple		translated_p;
	t_tuple		original_p;
	bool		ok;

	printf("Chapter 4: Multiplying by the inverse of a translation matrix\n");

	// --- Arrange: Set up the initial data ---
	transform = translation(5, -3, 2);
	p = point(-3, 4, 5);
	printf("%-30s", "Original point p:");
	print_tuple(p);
	printf("%-30s", "Forward translation matrix:");
	print_matrix(transform);

	// --- Act 1: Apply the forward translation ---
	translated_p = mat_mul_tuple(transform, p);
	printf("%-30s", "Point after forward translation:");
	print_tuple(translated_p);

	// --- Act 2: Apply the inverse translation ---
	inv_transform = mat_inverse(transform, &ok);
	printf("%-30s", "Inverse translation matrix:");
	print_matrix(inv_transform);
	original_p = mat_mul_tuple(inv_transform, translated_p);
	printf("%-30s", "Point after inverse translation:");
	print_tuple(original_p);

	// --- Assert: Check if the point is back where it started ---
	TEST_ASSERT(tuples_equal(original_p, p), "Point should return to original position");
	printf("\n");
}


/*
** Example: test_ch4_translation_ignores_vector()
** Description: Unit test to verify that translation does not affect vectors.
** Uses: translation(), vector(), mat_mul_tuple(), tuples_equal()
** Verified: Based on "The Raytracer Challenge", Chapter 4.
*/
void	test_ch4_translation_ignores_vector(void)
{
	t_matrix	transform;
	t_tuple		v;
	t_tuple		result_v;

	printf("Chapter 4: Translation does not affect vectors\n");
	
	// Arrange: Create translation matrix and a vector
	transform = translation(5, -3, 2);
	v = vector(-3, 4, 5);

	// Act: Apply the transformation
	result_v = mat_mul_tuple(transform, v);

	// Assert: Check that the vector remains unchanged
	printf("%-20s", "Original vector:");
	print_tuple(v);
	printf("%-20s", "Transformed vector:");
	print_tuple(result_v);
	TEST_ASSERT(tuples_equal(result_v, v), "Vector should not change after translation");
	printf("\n");
}

// --- Test functions from Chapter 5: Ray-Sphere Intersections ---

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

	// TODO: This test requires translation() function from Chapter 4
	// For now, we'll create a manual translation matrix
	double	values[4][4] = {
		{1, 0, 0, 3},
		{0, 1, 0, 4},
		{0, 0, 1, 5},
		{0, 0, 0, 1}
	};
	m = create_matrix(values);
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

	// TODO: This test requires scaling() function from Chapter 4
	// For now, we'll create a manual scaling matrix
	double	values[4][4] = {
		{2, 0, 0, 0},
		{0, 3, 0, 0},
		{0, 0, 4, 0},
		{0, 0, 0, 1}
	};
	m = create_matrix(values);
	r2 = ray_transform(r, m);

	TEST_ASSERT(tuples_equal(r2.origin, point(2, 6, 12)), "r2.origin = point(2, 6, 12)");
	TEST_ASSERT(tuples_equal(r2.direction, vector(0, 3, 0)), "r2.direction = vector(0, 3, 0)");
}

// --- Test functions from Chapter 5: Ray-Sphere Intersections ---

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
	t_xs			xs = xs_create(0);

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
	t_xs			xs = xs_create(0);

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
	t_xs			xs = xs_create(0);

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
	t_xs			xs = xs_create(0);

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
	t_xs			xs = xs_create(0);

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

/*
** Chapter 5: Sphere transformation tests
*/

// Helper functions for transformations (simplified versions for testing)

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

	// TODO: This test requires translation() function from Chapter 4
	// For now, we'll create a manual translation matrix
	double	values[4][4] = {
		{1, 0, 0, 2},
		{0, 1, 0, 3},
		{0, 0, 1, 4},
		{0, 0, 0, 1}
	};
	t = create_matrix(values);

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

	// TODO: This test requires scaling() function from Chapter 4
	// For now, we'll create a manual scaling matrix
	double	values[4][4] = {
		{2, 0, 0, 0},
		{0, 2, 0, 0},
		{0, 0, 2, 0},
		{0, 0, 0, 1}
	};
	scale = create_matrix(values);

	s = sphere_set_transform(s, scale);
	xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 2, "xs.count = 2");
	TEST_ASSERT(fabs(xs.intersections[0].t - 4.0) < EPS, "xs[0].t = 4");
	TEST_ASSERT(fabs(xs.intersections[1].t - 6.0) < EPS, "xs[1].t = 6");

	intersections_destroy(&xs);
}

void	test_ch5_intersecting_translated_sphere_with_ray(void)
{
	printf("Chapter 5: Intersecting a translated sphere with a ray\n");
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_sphere	s = sphere_create();
	t_matrix	translate;
	t_xs		xs;

	// TODO: This test requires translation() function from Chapter 4
	// For now, we'll create a manual translation matrix
	double	values[4][4] = {
		{1, 0, 0, 5},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	translate = create_matrix(values);

	s = sphere_set_transform(s, translate);
	xs = sphere_intersect(&s, r);

	TEST_ASSERT(xs.count == 0, "xs.count = 0");

	intersections_destroy(&xs);
}

// --- Add test functions for subsequent chapters here ---
// void test_ch.._.._.._..(void) { ... }

// --- Main function to run all book tests ---
int main(void)
{
	printf("--- Running 'The Raytracer Challenge' Book Tests ---\n\n");

	// Chapter 1
	test_ch1_tuple_is_point();
	test_ch1_tuple_is_vector();
	test_ch1_point_factory();
	test_ch1_vector_factory();
	test_ch1_add_two_tuples();
	test_ch1_substract_two_points();
	test_ch1_substract_v_from_p();
	test_ch1_substract_v_from_v();
	test_ch1_snegate_tupil();
	test_ch1_multiplying_a_tuple_by_a_scalar();
	test_ch1_multiplying_a_tuple_by_a_fraction();
	test_ch1_dividing_a_tuple_by_a_scalar();
	/*22May:*/
	test_ch1_magnitude_of_unit_vector_x();
	test_ch1_magnitude_of_unit_vector_y();
	test_ch1_magnitude_of_unit_vector_z();
	test_ch1_magnitude_of_vector1();
	test_ch1_magnitude_of_vector2();

	test_ch1_normalize_unit_vector();
	test_ch1_normalize_vector();
	test_ch1_magnitude_of_normalized_vector();

	test_ch1_dot_product_of_two_tuples();
	
	test_ch1_cross_product_of_two_vectors();
	test_ch1_cross_product_of_axes_vectors();
	/*26May :*/
	test_ch1_test_normalize_velocity();
	test_ch1_test_tick_updates_position_and_velocity();
	test_ch1_multiple_ticks();
	test_ch1_projectile_impact();
	/*27May :*/
	test_ch2_rgb_tuple_direct();
	/*28May :*/
	test_ch2_add_colors();
	test_ch2_substract_colors();
	test_ch2_multiplying_a_color_by_a_scalar();
	test_ch2_multiplying_two_colors();
	printf("\n");
	/*2June :*/
	test_ch2_creating_an_image();
	printf("\n");
	/*4June :*/
	test_ch2_writing_pixels();
	printf("\n");
	/*10June*/
	/*12June*/
	test_ch2_constructing_ppm_header();
	printf("\n");
	test_ch2_constructing_the_ppm_pixel_data();
	/*17June*/
	test_ch2_splitting_long_lines();
	/*18June*/
	printf("\n");
	test_ch2_newline_character_at_the_end();
	printf("\n");
	/*19June*/
	test_ch2_test_projectile_trajectory();
	printf("\n");
	/*23June*/
	test_ch3_matrix_construction();
	// Add calls to tests for subsequent chapters here
	// test_ch2_some_canvas_feature();
	printf("\n");
	/*4September*/
	test_ch3_identity_shape();
	printf("\n");
	test_ch3_matrix_equality();
	printf("\n");
	/*5September*/
	test_ch3_run_mat_mul_test();
	printf("\n");
	test_ch3_multiply_matrix_by_tuple();
	printf("\n");
	test_ch3_transpose_matrix();
	printf("\n");
	test_ch3_transpose_identity();
	printf("\n");
/*Here begin tests using submatrice, determinant for inversing using recursion:)*/
	test_ch3_determinant_2x2();
	printf("\n");
	test_ch3_submatrix_minor_cofactor();
	printf("\n");
	test_ch3_determinant_3x3_and_4x4();
	printf("\n");
	test_ch3_inversion();
	printf("\n");
	test_ch3_inverse_sanity_check();
	printf("\n");

	// --- Test functions from Chapter 5: Ray-Sphere Intersections ---
	test_ch5_creating_and_querying_ray();
	printf("\n");
	test_ch5_computing_point_from_distance();
	printf("\n");
	test_ch5_translating_ray();
	printf("\n");
	test_ch5_scaling_ray();
	printf("\n");

	// --- Test functions from Chapter 5: Ray-Sphere Intersections ---
	test_ch5_ray_intersects_sphere_at_two_points();
	printf("\n");
	test_ch5_ray_intersects_sphere_at_tangent();
	printf("\n");
	test_ch5_ray_misses_sphere();
	printf("\n");
	test_ch5_ray_originates_inside_sphere();
	printf("\n");
	test_ch5_sphere_is_behind_ray();
	printf("\n");
	
	// Chapter 5: Intersection tracking tests
	test_ch5_intersection_encapsulates_t_and_object();
	printf("\n");
	test_ch5_aggregating_intersections();
	printf("\n");
	test_ch5_intersect_sets_object_on_intersection();
	printf("\n");
	test_ch5_hit_when_all_intersections_have_positive_t();
	printf("\n");
	test_ch5_hit_when_some_intersections_have_negative_t();
	printf("\n");
	test_ch5_hit_when_all_intersections_have_negative_t();
	printf("\n");
	test_ch5_hit_is_always_lowest_nonnegative_intersection();
	printf("\n");

	// Chapter 5: Sphere transformation tests
	test_ch5_sphere_default_transformation();
	printf("\n");
	test_ch5_changing_sphere_transformation();
	printf("\n");
	test_ch5_intersecting_scaled_sphere_with_ray();
	printf("\n");
	test_ch5_intersecting_translated_sphere_with_ray();
	printf("\n");

	// Print test summary
	printf("========================================\n");
	printf("           TEST SUMMARY REPORT\n");
	printf("========================================\n");
	printf("Total tests run: %d\n", g_tests_run);
	printf("Tests passed: %d\n", g_tests_run - g_tests_failed);
	printf("Tests failed: %d\n", g_tests_failed);
	
	if (g_tests_failed > 0) {
		printf("\nFailed tests:\n");
		printf("-------------\n");
		for (int i = 0; i < g_tests_failed; i++) {
			printf("%d. %s\n", i + 1, g_failed_tests[i]);
		}
	} else {
		printf("\n🎉 All tests passed successfully!\n");
	}
	
	printf("========================================\n");
	/*11September*/
	printf("\n--- Chapter 4: Transformations ---\n");
	test_ch4_translation_moves_point();
	test_ch4_inverse_translation_moves_point_back();
	test_ch4_translation_ignores_vector();
	printf("\n");
	printf("--- All book tests finished. ---\n");
	return (g_tests_failed > 0 ? 1 : 0);
}

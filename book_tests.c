#include "include/tuples.h" // Указывай путь к твоим заголовочным файлам из src/
#include "include/projectile.h" // projectile.h includes environment.h

// #include "include/canvas.h" // For future chapters
// #include "include/matrices.h" // For future chapters
#include <stdio.h> // for printf

// --- Macro for displaying test results (optional, for clarity) ---
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define TEST_ASSERT(condition, message) \
	do { \
		printf("%-61s: ", message); \
		if (condition) { \
			printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET "\n"); \
		} else { \
			printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET "\n"); \
		} \
	} while (0)

///TO HELP PRINTING:

void	print_tuple(t_tuple	pt)
{
	printf("x=%.5f, y=%.5f, z=%.5f, w=%.5f\n",
		pt.x, pt.y, pt.z, pt.w);
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
	t_tuple	expected_vector = vector(0.26726, 0.53452, 0.80178);
	TEST_ASSERT(tuples_equal(normalized, expected_vector), "approximately vector(0.26726, 0.53452, 0.80178)");
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
	t_tuple	expected_vector = vector(0.26726, 0.53452, 0.80178);
	TEST_ASSERT(tuples_equal(norm, expected_vector), "approximately vector(0.26726, 0.53452, 0.80178)");
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

	// Ожидаемые значения после первого тика:
	// Позиция: (0 + 0.707, 1 + 0.707, 0) ≈ (0.707, 1.707, 0)
	// Скорость: (0.707 - 0.01, 0.707 - 0.1, 0) ≈ (0.697, 0.607, 0)

	TEST_ASSERT(tuples_equal(p.position, point(0.70711, 1.70711, 0)), 
				"Position after 1st tick should be (0.707, 1.707, 0)");

	TEST_ASSERT(tuples_equal(p.velocity, vector(0.69711, 0.60711, 0)), 
				"Velocity after 1st tick should be (0.697, 0.607, 0)");
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
	t_tuple expected_pos[] = {
		point(0.00000, 1.00000, 0),    // Tick 0 (initial state)
		point(0.70711, 1.70711, 0),    // Tick 1
		point(1.40422, 2.31422, 0),    // Tick 2
		point(2.09133, 2.82133, 0)     // Tick 3
	};

	t_tuple expected_vel[] = {
		vector(0.70711, 0.70711, 0),   // Tick 0 (initial velocity)
		vector(0.69711, 0.60711, 0),   // Tick 1
		vector(0.68711, 0.50711, 0),   // Tick 2
		vector(0.67711, 0.40711, 0)    // Tick 3
	};

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
	TEST_ASSERT(p.position.y <= 0.0 + EPSILON, 
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
void	test_ch2_rgb_tuple_direct(void)
{
	printf("Chapter 2: color(-0.5, 0.4, 1.7) direct values: 0 - 1\n\n");
	t_tuple color = vector(-0.5, 0.4, 1.7);//color = vector
	TEST_ASSERT(floats_equal(color.x, -0.5), "RED color.x = -0.5");
	TEST_ASSERT(floats_equal(color.y, 0.4), "GREEN color.y = 0.4");
	TEST_ASSERT(floats_equal(color.z, 1.7), "BLUE color.z = 1.7");
	printf("\n");
	TEST_ASSERT(floats_equal(color.w, 0.0), "color.w = 0.0");
	TEST_ASSERT(is_point(color) == 0, "color is not a point");
	TEST_ASSERT(is_vector(color) == 1, "color a is a vector");
	printf("\n");
	print_tuple(color);
	printf("\n");
}

// --- Add test functions for subsequent chapters here ---
// void test_ch2_some_canvas_feature(void) { ... }

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

	printf("\n");
	// Add calls to tests for subsequent chapters here
	// test_ch2_some_canvas_feature();
	// printf("\n");

	printf("--- All book tests finished. ---\n");
	return (0);
}

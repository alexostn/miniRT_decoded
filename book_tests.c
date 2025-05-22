#include "include/tuples.h" // Указывай путь к твоим заголовочным файлам из src/
// #include "include/canvas.h" // For future chapters
// #include "include/matrices.h" // For future chapters
#include <stdio.h> // for printf

// --- Macro for displaying test results (optional, for clarity) ---
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define TEST_ASSERT(condition, message) \
    do { \
        printf("  - %-58s: ", message); \
        if (condition) { \
            printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET "\n"); \
        } else { \
            printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET "\n"); \
        } \
    } while (0)

// --- Test functions from Chapter 1: Tuples, Points, and Vectors ---
void test_ch1_tuple_is_point(void)
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
	t_tuple sum = add_two_tuples(a1, a2);
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
	/*today 22May:*/
	test_ch1_magnitude_of_unit_vector_x();
	test_ch1_magnitude_of_unit_vector_y();
	test_ch1_magnitude_of_unit_vector_z();
	test_ch1_magnitude_of_vector1();
	test_ch1_magnitude_of_vector2();

	printf("\n");

	// Add calls to tests for subsequent chapters here
    // test_ch2_some_canvas_feature();
    // printf("\n");

    printf("--- All book tests finished. ---\n");
    return (0);
}

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
        printf("  - %-42s: ", message); \
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

// Scenario: Subtracting a vector from the zero vector
// Given zero ← vector(0, 0, 0)
// And v ← vector(1, -2, 3)
// Then zero - v = vector(-1, 2, -3)

void test_ch1_snegate_tupil(void)
{
	printf("Chapter 1: Substracting a vector from a vector(v1 - v2)\n");
	// t_tuple given_zero = vector(0, 0, 0);
	t_tuple v = vector(1, -2, 3);
	t_tuple negated = negate_tupil(v);
	t_tuple expected_vector = vector(-1, 2, -3);
	TEST_ASSERT(tuples_equal(expected_vector, negated), " negated = vector(-1, 2, -3)");
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
	printf("\n");

	// Add calls to tests for subsequent chapters here
    // test_ch2_some_canvas_feature();
    // printf("\n");

    printf("--- All book tests finished. ---\n");
    return (0);
}

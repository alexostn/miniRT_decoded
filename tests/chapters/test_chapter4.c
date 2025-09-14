#include "../test_common.h"

// Chapter 4: Transformations - Complete with all 3 tests

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

// Main function to run all Chapter 4 tests
void run_chapter4_tests(void)
{
	printf("\n=== Chapter 4: Transformations ===\n");
	
	test_ch4_translation_moves_point();
	test_ch4_inverse_translation_moves_point_back();
	test_ch4_translation_ignores_vector();
	
	printf("\n=== Chapter 4 Tests Complete ===\n\n");
}
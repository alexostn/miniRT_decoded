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

void	test_ch4_scaling_point(void)
{
	t_matrix    transform;
	t_tuple     v;
	t_tuple     result;
	t_tuple     expected;

	printf("Chapter 4: A scaling matrix applied to a point\n");

	// Arrange: Create scaling matrix and point
	transform = scaling(2, 3, 4);
	v = point(-4, 6, 8);
	expected = point(-8, 18, 32);

	// Act: Apply the transformation
	result = mat_mul_tuple(transform, v);

	// Assert: Check if the point was scaled correctly
	printf("%-20s", "Original point:");
	print_tuple(v);
	printf("%-20s", "Scaling matrix:");
	print_matrix(transform);
	printf("%-20s", "Scaled point:");
	print_tuple(result);
	TEST_ASSERT(tuples_equal(result, expected), "point should be scaled to (-8, 18, 32)");
	printf("\n");
}

void    test_ch4_scaling_vector(void)
{
	t_matrix    transform;
	t_tuple     v;
	t_tuple     result;
	t_tuple     expected;

	printf("Chapter 4: A scaling matrix applied to a vector\n");

	// Arrange: Create scaling matrix and vector
	transform = scaling(2, 3, 4);
	v = vector(-4, 6, 8);
	expected = vector(-8, 18, 32);

	// Act: Apply the transformation
	result = mat_mul_tuple(transform, v);

	// Assert: Check if the vector was scaled correctly
	printf("%-20s", "Original vector:");
	print_tuple(v);
	printf("%-20s", "Scaling matrix:");
	print_matrix(transform);
	printf("%-20s", "Scaled vector:");
	print_tuple(result);
	TEST_ASSERT(tuples_equal(result, expected), "Vector should be scaled to (-8, 18, 32)");
	printf("\n");
}

void	test_ch4_mult_by_inverse_of_scaling_matrix(void)
{
	t_matrix	transform;
	t_matrix	inv;
	t_tuple     v;
	t_tuple     result;
	t_tuple     expected;
	bool		is_invertible;
	printf("Chapter 4: Multiplying by the inverse of a scaling matrix\n");

	// Arrange: Create scaling matrix and vector
	transform = scaling(2, 3, 4);
	inv = mat_inverse(transform, &is_invertible);
	v = vector(-4, 6, 8);
	expected = vector(-2, 2, 2);

	// Act: Apply the transformation
	result = mat_mul_tuple(inv, v);

	// Assert: Check if the vector was scaled correctly
	printf("%-20s", "Original vector:");
	print_tuple(v);
	printf("%-20s", "Scaling matrix:");
	print_matrix(transform);
	printf("%-20s", "Inverted matrix:");
	print_matrix(inv);
	printf("%-20s", "Scaled vector:");
	print_tuple(result);
	TEST_ASSERT(tuples_equal(result, expected), "Vector * inverted matrix = vector should be scaled to (-2, 2, 2)");
	printf("\n");
}

void	test_ch4_reflection_scaling_by_negative(void)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;
	t_tuple		expected;

	printf("Chapter 4: Reflection is scaling by a negative value\n");

	// Arrange: Create scaling matrix and point
	transform = scaling(-1, 1, 1);
	p = point(2, 3, 4);
	expected = point(-2, 3, 4);

	// Act: Apply the transformation
	result = mat_mul_tuple(transform, p);

	// Assert: Check if the point was scaled correctly
	printf("%-20s", "Original point:");
	print_tuple(p);
	printf("%-20s", "Scaling matrix:");
	printf("%-20s", "could be changed in any other direction x, y, z");
	print_matrix(transform);
	printf("%-20s", "Scaled reflected point:");
	print_tuple(result);
	TEST_ASSERT(tuples_equal(result, expected), "Point scaled to (-2, 3, 4) or reflected");
	printf("\n");
}

void	test_degrees_to_radians(void)
{
	double	rad;
	double	expected;

	printf("Chapter 4: Helper to convert degrees to radians\n");

	rad = degrees_to_radians(90.0);
	expected = M_PI / 2.0;
	TEST_ASSERT(fabs(rad - expected) < EPS, "90 degrees should be PI/2");

	rad = degrees_to_radians(180.0);
	expected = M_PI;
	TEST_ASSERT(fabs(rad - expected) < EPS, "180 degrees should be PI");

	rad = degrees_to_radians(45.0);
	expected = M_PI / 4.0;
	TEST_ASSERT(fabs(rad - expected) < EPS, "45 degrees should be PI/4");

	rad = degrees_to_radians(360.0);
	expected = 2 * M_PI;
	TEST_ASSERT(fabs(rad - expected) < EPS, "360 degrees should be 2*PI");
	printf("\n");
}

void	test_ch4_rotation_x(void)
{
	t_tuple		p;
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_tuple		result;

	printf("Chapter 4: Rotating a point around the x axis\n\n");

	// --- Test case 1: Rotation by 45 degrees (PI / 4) ---
	printf("--- Test Case 1: Rotation by 45 degrees ---\n");
	p = point(0, 1, 0);
	half_quarter = rotation_x(M_PI / 4);
	
	printf("Original point:\n");
	print_tuple(p);
	printf("Rotation matrix (45 deg):\n");
	print_matrix(half_quarter);
	result = mat_mul_tuple(half_quarter, p);
	printf("Result after rotation:\n");
	print_tuple(result);

	TEST_ASSERT(tuples_equal(result, point(0, sqrt(2) / 2, sqrt(2) / 2)),
		"Rotation by half_quarter (45 deg)");
	printf("\n");

	// --- Test case 2: Rotation by 90 degrees (PI / 2) ---
	printf("--- Test Case 2: Rotation by 90 degrees ---\n");
	p = point(0, 1, 0);
	full_quarter = rotation_x(M_PI / 2);

	printf("Original point:\n");
	print_tuple(p);
	printf("Rotation matrix (90 deg):\n");
	print_matrix(full_quarter);
	result = mat_mul_tuple(full_quarter, p);
	printf("Result after rotation:\n");
	print_tuple(result);

	TEST_ASSERT(tuples_equal(result, point(0, 0, 1)),
		"Rotation by full_quarter (90 deg)");
	printf("\n");
}

void    test_ch4_rotation_x_inversed(void)
{
	t_tuple     p;
	t_matrix    half_quarter;
	t_matrix    inv;
	bool        is_invertible;
	t_tuple     result;

	printf("--- Chapter 4: Inverse of an x-rotation ---\n\n");

	// --- Arrange: Set up the rotation and the point ---
	p = point(0, 1, 0);
	half_quarter = rotation_x(M_PI / 4);

	// --- Act: Calculate the inverse matrix and apply it ---
	inv = mat_inverse(half_quarter, &is_invertible);
	result = mat_mul_tuple(inv, p);

	printf("Original point:\n");
	print_tuple(p);
	printf("Rotation matrix (+45 deg):\n");
	print_matrix(half_quarter);
	printf("INVERSE of the rotation matrix (-45 deg):\n");
	print_matrix(inv);
	printf("Result after applying INVERSE rotation:\n");
	print_tuple(result);

	TEST_ASSERT(tuples_equal(result, point(0, sqrt(2) / 2, -sqrt(2) / 2)),
		"Inverse rotation by half_quarter (-45 deg)");
	printf("\n");
}

void	test_ch4_rotation_y(void)
{
	t_tuple		p;
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_tuple		result;

	printf("Chapter 4: Rotating a point around the y axis\n\n");

	// --- Test case 1: Rotation by 45 degrees (PI / 4) ---
	printf("--- Test Case 1: Rotation by 45 degrees ---\n");
	p = point(0, 0, 1);
	half_quarter = rotation_y(M_PI / 4);

	printf("Original point:\n");
	print_tuple(p);
	printf("Rotation matrix (45 deg):\n");
	print_matrix(half_quarter);
	result = mat_mul_tuple(half_quarter, p);
	printf("Result after rotation:\n");
	print_tuple(result);

	TEST_ASSERT(tuples_equal(result, point(sqrt(2) / 2, 0, sqrt(2) / 2)),
		"Rotation by half_quarter (45 deg)");
	printf("\n");

	// --- Test case 2: Rotation by 90 degrees (PI / 2) ---
	printf("--- Test Case 2: Rotation by 90 degrees ---\n");
	p = point(0, 0, 1);
	full_quarter = rotation_y(M_PI / 2);
	printf("Original point:\n");
	print_tuple(p);
	printf("Rotation matrix (90 deg):\n");
	print_matrix(full_quarter);
	result = mat_mul_tuple(full_quarter, p);
	printf("Result after rotation:\n");
	print_tuple(result);

	TEST_ASSERT(tuples_equal(result, point(1, 0, 0)),
		"Rotation by full_quarter (90 deg)");
	printf("\n");
}

void	test_ch4_rotation_z(void)
{
	t_tuple		p;
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_tuple		result;

	printf("Chapter 4: Rotating a point around the z axis\n\n");

	// --- Test case 1: Rotation by 45 degrees (PI / 4) ---
	printf("--- Test Case 1: Rotation by 45 degrees ---\n");
	p = point(0, 1, 0);
	half_quarter = rotation_z(M_PI / 4);

	printf("Original point:\n");
	print_tuple(p);
	printf("Rotation matrix (45 deg):\n");
	print_matrix(half_quarter);

	result = mat_mul_tuple(half_quarter, p);
	printf("Result after rotation:\n");
	print_tuple(result);

	TEST_ASSERT(tuples_equal(result, point(-sqrt(2) / 2, sqrt(2) / 2, 0)),
		"Rotation by half_quarter (45 deg)");
	printf("\n");

	// --- Test case 2: Rotation by 90 degrees (PI / 2) ---
	printf("--- Test Case 2: Rotation by 90 degrees ---\n");
	p = point(0, 1, 0);
	full_quarter = rotation_z(M_PI / 2);

	printf("Original point:\n");
	print_tuple(p);
	printf("Rotation matrix (90 deg):\n");
	print_matrix(full_quarter);
	result = mat_mul_tuple(full_quarter, p);
	printf("Result after rotation:\n");
	print_tuple(result);

	TEST_ASSERT(tuples_equal(result, point(-1, 0, 0)),
		"Rotation by full_quarter (90 deg)");
	printf("\n");
}

// Main function to run all Chapter 4 tests
void run_chapter4_tests(void)
{
	printf("\n=== Chapter 4: Transformations ===\n");
	
	test_ch4_translation_moves_point();
	test_ch4_inverse_translation_moves_point_back();
	test_ch4_translation_ignores_vector();
	test_ch4_scaling_point();
	test_ch4_scaling_vector();
	test_ch4_mult_by_inverse_of_scaling_matrix();
	test_ch4_reflection_scaling_by_negative();
	/*Rotation*/
	test_degrees_to_radians();
	printf("\n");
	test_ch4_rotation_x();
	printf("\n");
	/*12September*/
	test_ch4_rotation_x_inversed();
	printf("\n");
	test_ch4_rotation_y();
	printf("\n");
	test_ch4_rotation_z();

	printf("\n=== Chapter 4 Tests Complete ===\n\n");
}
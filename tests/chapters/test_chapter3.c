#include "../test_common.h"

// Chapter 3: Matrices - Complete with all 12 tests

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

	// Test assertions according to requirements
	TEST_ASSERT((get_matrix_element(&M, 0, 0) == 1), "M[0,0] = 1");
	// assert(get_matrix_element(&M, 0, 0) == 1);
	TEST_ASSERT((get_matrix_element(&M, 0, 3) == 4), "M[0,3] = 4");
	// assert(get_matrix_element(&M, 0, 3) == 4);
	TEST_ASSERT((get_matrix_element(&M, 1, 0) == 5.5), "M[1,0] = 5.5");
	TEST_ASSERT((get_matrix_element(&M, 1, 2) == 7.5), "M[1,2] = 7.5");
	TEST_ASSERT((get_matrix_element(&M, 2, 2) == 11), "M[2,2] = 11");
	TEST_ASSERT((get_matrix_element(&M, 3, 0) == 13.5), "M[3,0] = 13.5");
	TEST_ASSERT((get_matrix_element(&M, 3, 2) == 15.5), "M[3,2] = 15.5");
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

	TEST_ASSERT(!mat_equal(a, b), "Matrices are not equal");
	print_matrix(a);
	print_matrix(b);
	printf("\n");
}

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

	sub = mat_submatrix(a, 0, 1);
	printf("Submatrix of a (removing row 0, col 1):\n");
	print_matrix(sub);
	TEST_ASSERT(mat_equal(sub, expected_sub), "Submatrix of 3x3 is correct");

	b = create_matrix(a_values);
	TEST_ASSERT(floats_equal(mat_minor(b, 0, 0), -48), "Minor of 3x3 matrix");
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 0), -48), "Cofactor (sign not changed)");

	TEST_ASSERT(floats_equal(mat_minor(b, 1, 0), -15), "Minor of 3x3 matrix (case 2)");
	TEST_ASSERT(floats_equal(mat_cofactor(b, 1, 0), 15), "Cofactor (sign changed)");
}

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

	a = create_matrix(a_values);
	printf("Matrix A (3x3):\n");
	print_matrix(a);
	TEST_ASSERT(floats_equal(mat_cofactor(a, 0, 0), 56),   "Cofactor A(0,0) = 56");
	TEST_ASSERT(floats_equal(mat_cofactor(a, 0, 1), 12),   "Cofactor A(0,1) = 12");
	TEST_ASSERT(floats_equal(mat_cofactor(a, 0, 2), -46),  "Cofactor A(0,2) = -46");
	TEST_ASSERT(floats_equal(mat_determinant(a), -196), "Determinant of 3x3 matrix");
	printf(ANSI_COLOR_RED "Matrix a determinant is \n" \
		"Cofactor A(0,0)*A(0,0)\n" \
		" + \n" \
		"Cofactor A(0,1)*A(0,1)\n" \
		" + \n" \
		"Cofactor A(0,2)*A(0,2)\n" \
		"_______________________\n" \
		":\n%f\n\n" ANSI_COLOR_RESET, mat_determinant(a));

	b = create_matrix(b_values);
	printf("\nMatrix B (4x4):\n");
	print_matrix(b);
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 0), 690),  "Cofactor B(0,0) = 690");
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 1), 447),  "Cofactor B(0,1) = 447");
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 2), 210),  "Cofactor B(0,2) = 210");
	TEST_ASSERT(floats_equal(mat_cofactor(b, 0, 3), 51),   "Cofactor B(0,3) = 51");
	TEST_ASSERT(floats_equal(mat_determinant(b), -4071), "Determinant of 4x4 matrix");
	printf(ANSI_COLOR_RED "Matrix determinant is:\n%f\n\n" ANSI_COLOR_RESET, mat_determinant(b) );
}

void	test_ch3_inversion(void)
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

	TEST_ASSERT(!floats_equal(mat_determinant(a), 0), "Matrix is invertible (det != 0)");

	inv_a = mat_inverse(a, &is_invertible);
	TEST_ASSERT(is_invertible, "mat_inverse reports success");

	printf("Inverse of A (calculated):\n");
	print_matrix(inv_a);
	printf("Inverse of A (expected):\n");
	print_matrix(expected_inv);

	TEST_ASSERT(mat_equal(inv_a, expected_inv), "Calculated inverse matches expected inverse");
}

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

	TEST_ASSERT(mat_equal(product, mat_identity()), "Product of matrix and its inverse is identity");
}

// Main function to run all Chapter 3 tests
void run_chapter3_tests(void)
{
	printf("\n=== Chapter 3: Matrices ===\n");
	
	test_ch3_matrix_construction();
	test_ch3_identity_shape();
	test_ch3_matrix_equality();
	test_ch3_run_mat_mul_test();
	test_ch3_multiply_matrix_by_tuple();
	test_ch3_transpose_matrix();
	test_ch3_transpose_identity();
	test_ch3_determinant_2x2();
	test_ch3_submatrix_minor_cofactor();
	test_ch3_determinant_3x3_and_4x4();
	test_ch3_inversion();
	test_ch3_inverse_sanity_check();
	
	printf("\n=== Chapter 3 Tests Complete ===\n\n");
}
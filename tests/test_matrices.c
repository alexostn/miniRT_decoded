#include "matrices.h"
#include "test_matrices.h"

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
	double values[4][4] = {
		{1, 2, 3, 4},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5}
	};

	t_matrix M = create_matrix(values);

	// Проверки согласно тесту
	// TEST_ASSERT((get_matrix_element(&M, 0, 0) == 1), "M[0,0] = 1");
	assert(get_matrix_element(&M, 0, 0) == 1);
	assert(get_matrix_element(&M, 0, 3) == 4);
	assert(get_matrix_element(&M, 1, 0) == 5.5);
	assert(get_matrix_element(&M, 1, 2) == 7.5);
	assert(get_matrix_element(&M, 2, 2) == 11);
	assert(get_matrix_element(&M, 3, 0) == 13.5);
	assert(get_matrix_element(&M, 3, 2) == 15.5);
}

int main(void)
{
	printf("--- Running 'The Matrices Tests ---\n\n");

	// Chapter 3
	test_ch3_matrix_construction();
	printf("--- All Matrices tests finished. ---\n");
	return (0);
}

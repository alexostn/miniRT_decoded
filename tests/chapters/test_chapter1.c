#include "../test_common.h"

// Chapter 1: Tuples, Points, and Vectors - Complete with all 27 tests

void	test_ch1_tuple_is_point(void)
{
	printf("Chapter 1: A tuple with w=1.0 is a point\n");
	t_tuple a = tuple(4.3, -4.2, 3.1, 1.0);
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

void test_ch1_add_two_tuples(void)
{
	printf("Chapter 1: Adding two tuples\n");
	t_tuple a1 = tuple(3, -2, 5, 1.0);
	t_tuple a2 = tuple(-2, 3, 1, 0.0);
	t_tuple sum = add(a1, a2);
	t_tuple expected = tuple(1, 1, 6, 1.0);
	TEST_ASSERT(tuples_equal(expected, sum), "sum = tuple(1, 1, 6, 1)");
}

void test_ch1_substract_two_points(void)
{
	printf("Chapter 1: Substracting two points(p1 - p2)\n");
	t_tuple p1 = point(3, 2, 1);
	t_tuple p2 = point(5, 6, 7);
	t_tuple diff = substract_tuples(p1, p2);
	t_tuple expected_vector = vector(-2, -4, -6);
	TEST_ASSERT(tuples_equal(expected_vector, diff), " diff = vector(-2, -4, -6)");
}

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

void test_ch1_snegate_tupil(void)
{
	printf("Chapter 1: Substracting a vector from a vector(v1 - v2)\n");
	t_tuple v = vector(1, -2, 3);
	t_tuple negated = negate_tupil(v);
	t_tuple expected_vector = vector(-1, 2, -3);
	TEST_ASSERT(tuples_equal(expected_vector, negated), " negated = vector(-1, 2, -3)");
}

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

void test_ch1_dividing_a_tuple_by_a_scalar(void)
{
	printf("Chapter 1: Dividing a tuple by a scalar\n");
	t_tuple	d = tuple(1, -2, 3, -4);
	double	scalar = 2;
	t_tuple	tquotient = divide_tuple_scalar(d, scalar);
	t_tuple	expected_tuple = tuple(0.5, -1, 1.5, -2);
	TEST_ASSERT(tuples_equal(tquotient, expected_tuple), "quotient = tuple(0.5, -1, 1.5, -2)");
}

void test_ch1_magnitude_of_unit_vector_x(void)
{
	printf("Chapter 1: Computing the magnitude of X unit vector(1, 0, 0)\n");
	t_tuple	v = vector(1, 0, 0);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 1;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = 1");
}

void test_ch1_magnitude_of_unit_vector_y(void)
{
	printf("Chapter 1: Computing the magnitude of Y unit vector(0, 1, 0)\n");
	t_tuple	v = vector(0, 1, 0);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 1;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = 1");
}

void test_ch1_magnitude_of_unit_vector_z(void)
{
	printf("Chapter 1: Computing the magnitude of Z unit vector(0, 0, 1)\n");
	t_tuple	v = vector(0, 0, 1);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 1;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = 1");
}

void test_ch1_magnitude_of_vector1(void)
{
	printf("Chapter 1: Computing the magnitude of vector(1, 2, 3)\n");
	t_tuple	v = vector(1, 2, 3);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 3.741657387;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = √14");
}

void test_ch1_magnitude_of_vector2(void)
{
	printf("Chapter 1: Computing the magnitude of vector(-1, -2, -3)\n");
	t_tuple	v = vector(-1, -2, -3);
	double magnitude = magnitude_of_vector(v);
	double expected_magnitude = 3.741657387;
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(v) = √14");
}

void	test_ch1_normalize_unit_vector(void)
{
	printf("Chapter 1: Normalizing vector(4, 0, 0) gives (1, 0, 0)\n");
	t_tuple	v = vector(4, 0, 0);
	t_tuple	normalized = normalize_vector(v);
	t_tuple	expected_vector = vector(1, 0, 0);
	TEST_ASSERT(tuples_equal(normalized, expected_vector), "normalize(v) = vector(1, 0, 0)");
}

void	test_ch1_normalize_vector(void)
{
	printf("Chapter 1: Normalizing vector(1, 2, 3)\n");
	t_tuple	v = vector(1, 2, 3);
	t_tuple	normalized = normalize_vector(v);
	double inv = 1.0 / sqrt(14.0);
	t_tuple expected_vector = vector(1.0*inv, 2.0*inv, 3.0*inv);
	TEST_ASSERT(tuples_equal(normalized, expected_vector),
"approximately vector(1/sqrt14, 2/sqrt14, 3/sqrt14)");
}

void test_ch1_magnitude_of_normalized_vector(void)
{
	printf("Chapter 1: The magnitude of a normalized vector(1, 2, 3)\n");
	t_tuple	v = vector(1, 2, 3);
	t_tuple	norm = normalize_vector(v);
	double magnitude = magnitude_of_vector(norm);
	double expected_magnitude = 1;
	double inv = 1.0 / sqrt(14.0);
	t_tuple expected_vector = vector(1.0*inv, 2.0*inv, 3.0*inv);
	TEST_ASSERT(tuples_equal(norm, expected_vector), "approximately vector(1/sqrt14, 2/sqrt14, 3/sqrt14)");
	TEST_ASSERT(floats_equal(magnitude, expected_magnitude), "magnitude(norm) = 1");
}

void	test_ch1_dot_product_of_two_tuples(void)
{
	printf("Chapter 1: The dot product of two tuples\n");
	t_tuple	a = vector(1, 2, 3);
	t_tuple	b= vector(2, 3, 4);
	double	dot = dot_product(a, b);
	double	expected_dot = 20;
	TEST_ASSERT(floats_equal(dot, expected_dot), "dot(a, b) = 20");
}

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
	t_projectile p = projectile_create(point(0, 1, 0), vector(1, 1, 0));
	t_environment env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};

	p = tick(env, p);

	double	inv = 1.0 / sqrt(2.0);
	t_tuple	expected_pos = point(inv, 1.0 + inv, 0.0);
	t_tuple	expected_vel = vector(inv - 0.01, inv - 0.1, 0.0);
	TEST_ASSERT(tuples_equal(p.position, expected_pos),
			"Position after 1st tick should be (~inv, 1+inv, 0)");
	TEST_ASSERT(tuples_equal(p.velocity, expected_vel),
			"Velocity after 1st tick should be (~inv-0.01, ~inv-0.1, 0)");
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

	printf("=== Initial state (tick 0) ===\n");
	printf("Given position:		"); print_tuple(p.position);
	printf("Given velocity:		"); print_tuple(vector(1, 1, 0));
	printf("Normalized velocity:	"); print_tuple(p.velocity);
	TEST_ASSERT(tuples_equal(p.position, expected_pos[0]), "Initial position");
	TEST_ASSERT(tuples_equal(p.velocity, expected_vel[0]), "Initial velocity");

	for (int i = 1; i <= 3; i++) 
	{
		p = tick(env, p);
		
		printf("\n=== After tick %d ===\n", i);
		printf("Expected position: "); print_tuple(expected_pos[i]);
		printf("Expected velocity: "); print_tuple(expected_vel[i]);
		
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

	TEST_ASSERT(p.position.y <= 0.0 + EPS, 
				"Projectile Y > 0 (actual Y)");

	int expected_ticks = 17;
	TEST_ASSERT(floats_equal(ticks, expected_ticks), "Expected ticks:	");
	TEST_ASSERT(floats_equal(ticks, expected_ticks), "are equal");
	printf("= %d\n\n", expected_ticks);

        if (!floats_equal(ticks, expected_ticks))
        {
                printf("Final position: ");
                print_tuple(p.position);
                printf("Velocity at impact: ");
                print_tuple(p.velocity);
        }
}

//TODO ON CANVAS:
// " Then, run tick repeatedly until the projectile's y position is less than or equal
// to 0. Report the projectile's position after each tick, and the number of ticks
// it takes for the projectile to hit the ground. Try multiplying the projectile's
// initial velocity by larger and larger numbers to see how much farther the
// projectile goes! "

// Main function to run all Chapter 1 tests
void run_chapter1_tests(void)
{
	printf("\n=== Chapter 1: Tuples, Points, and Vectors ===\n");
	
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
	test_ch1_test_normalize_velocity();
	test_ch1_test_tick_updates_position_and_velocity();
	test_ch1_multiple_ticks();
	test_ch1_projectile_impact();
	
	printf("\n=== Chapter 1 Tests Complete ===\n\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chapter13.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:20:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/10 12:20:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_common.h"
#include "cylinders.h"
#include "cones.h"

static void	assert_close(double a, double b, const char *msg)
{
	TEST_ASSERT(fabs(a - b) < 1e-4, msg);
}

/* === Cylinders: misses === */
static void	cyl_ray_misses(void)
{
	t_cylinder	cyl;
	t_ray		r;
	t_xs		xs;

	printf("Chapter 13: Cylinder ray misses\n");
	cyl = cylinder_create();
	r = ray(point(1, 0, 0), normalize_vector(vector(0, 1, 0)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 0, "miss from side");

	r = ray(point(0, 0, 0), normalize_vector(vector(0, 1, 0)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 0, "miss from inside parallel");

	r = ray(point(0, 0, -5), normalize_vector(vector(1, 1, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 0, "miss skewed from outside");
}

/* === Cylinders: hits === */
static void	cyl_ray_hits(void)
{
	t_cylinder	cyl;
	t_ray		r;
	t_xs		xs;

	printf("Chapter 13: Cylinder ray hits\n");
	cyl = cylinder_create();
	r = ray(point(1, 0, -5), normalize_vector(vector(0, 0, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 2, "tangent counts=2");
	assert_close(xs.intersections[0].t, 5.0, "t0 = 5");
	assert_close(xs.intersections[1].t, 5.0, "t1 = 5");

	r = ray(point(0, 0, -5), normalize_vector(vector(0, 0, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 2, "perpendicular counts=2");
	assert_close(xs.intersections[0].t, 4.0, "t0 = 4");
	assert_close(xs.intersections[1].t, 6.0, "t1 = 6");

	r = ray(point(0.5, 0, -5), normalize_vector(vector(0.1, 1, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 2, "skewed counts=2");
	assert_close(xs.intersections[0].t, 6.80798, "t0 ~ 6.80798");
	assert_close(xs.intersections[1].t, 7.08872, "t1 ~ 7.08872");
}

/* === Cylinders: normals === */
static void	cyl_normals(void)
{
	t_cylinder	cyl;

	printf("Chapter 13: Cylinder normals\n");
	cyl = cylinder_create();
	TEST_ASSERT(tuples_equal(cylinder_local_normal_at(&cyl, point(1, 0, 0)),
			vector(1, 0, 0)), "n at +x");
	TEST_ASSERT(tuples_equal(cylinder_local_normal_at(&cyl, point(0, 5, -1)),
			vector(0, 0, -1)), "n at -z");
	TEST_ASSERT(tuples_equal(cylinder_local_normal_at(&cyl, point(0, -2, 1)),
			vector(0, 0, 1)), "n at +z");
	TEST_ASSERT(tuples_equal(cylinder_local_normal_at(&cyl, point(-1, 1, 0)),
			vector(-1, 0, 0)), "n at -x");
}

/* === Cylinders: truncation and caps === */
static void	cyl_truncate_and_caps(void)
{
	t_cylinder	cyl;
	t_ray		r;
	t_xs		xs;

	printf("Chapter 13: Cylinder truncation & caps\n");
	cyl = cylinder_create();
	TEST_ASSERT(isinf(cyl.minimum) && isinf(cyl.maximum),
		"default min/max are infinite");

	/* constrained */
	cyl.minimum = 1.0;
	cyl.maximum = 2.0;
	r = ray(point(0, 1.5, 0), normalize_vector(vector(0.1, 1, 0)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 0, "constrained #1");
	r = ray(point(0, 3, -5), normalize_vector(vector(0, 0, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 0, "constrained #2");
	r = ray(point(0, 0, -5), normalize_vector(vector(0, 0, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 0, "constrained #3");
	r = ray(point(0, 2, -5), normalize_vector(vector(0, 0, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 0, "constrained #4");
	r = ray(point(0, 1, -5), normalize_vector(vector(0, 0, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 0, "constrained #5");
	r = ray(point(0, 1.5, -2), normalize_vector(vector(0, 0, 1)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 2, "constrained #6 (two hits)");

	/* caps */
	cyl.closed = false;
	TEST_ASSERT(!cyl.closed, "default closed is false");
	cyl.closed = true;
	r = ray(point(0, 3, 0), normalize_vector(vector(0, -1, 0)));
	xs = cylinder_local_intersect(&cyl, r);
	TEST_ASSERT(xs.count == 2, "caps #1 two hits");
}

/* === Cones basic tests (subset) === */
static void	cones_basic(void)
{
	t_cone	cone;
	t_ray	r;
	t_xs	xs;

	printf("Chapter 13: Cones basic\n");
	cone = cone_create();
	r = ray(point(0, 0, -5), normalize_vector(vector(0, 0, 1)));
	xs = cone_local_intersect(&cone, r);
	TEST_ASSERT(xs.count == 2, "cone hit tangent");

    r = ray(point(0, 0, -5), normalize_vector(vector(1, 1, 1)));
    xs = cone_local_intersect(&cone, r);
    TEST_ASSERT(xs.count >= 1, "cone hit skewed (at least one)");
}

void	run_chapter13_tests(void)
{
	printf("\n=== Chapter 13: Cylinders & Cones ===\n");
	cyl_ray_misses();
	cyl_ray_hits();
	cyl_normals();
	cyl_truncate_and_caps();
	cones_basic();
	printf("\n=== Chapter 13 Tests Complete ===\n\n");
}

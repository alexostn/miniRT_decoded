/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_chapter9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:22:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/04 12:22:00 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_common.h"
#include "shapes.h"
#include "planes.h"

static t_tuple	local_normal_testshape(t_tuple p)
{
	return (vector(p.x, p.y, p.z));
}

static void	shape_ray_saved_after_transform(void)
{
	t_shape	 s;
	t_ray	 r;
	t_ray	 saved;

	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = shape_create();
	s = shape_set_transform(s, scaling(2, 2, 2));
	saved = shape_transform_ray_to_local(&s, r);
	TEST_ASSERT(tuples_equal(saved.origin, point(0, 0, -2.5)),
		"saved_ray.origin = point(0,0,-2.5)");
	TEST_ASSERT(tuples_equal(saved.direction, vector(0, 0, 0.5)),
		"saved_ray.direction = vector(0,0,0.5)");
}

static void	shape_ray_saved_after_translation(void)
{
	t_shape	 s;
	t_ray	 r;
	t_ray	 saved;

	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = shape_create();
	s = shape_set_transform(s, translation(5, 0, 0));
	saved = shape_transform_ray_to_local(&s, r);
	TEST_ASSERT(tuples_equal(saved.origin, point(-5, 0, -5)),
		"saved_ray.origin = point(-5,0,-5)");
	TEST_ASSERT(tuples_equal(saved.direction, vector(0, 0, 1)),
		"saved_ray.direction = vector(0,0,1)");
}

static void	shape_default_transform_material(void)
{
	t_shape	 s;

	s = shape_create();
	TEST_ASSERT(mat_equal(s.transform, mat_identity()),
		"shape default transform is identity");
	TEST_ASSERT(material_equal(s.material, material_create()),
		"shape default material");
}

static void	shape_assign_transform_material(void)
{
	t_shape	 s;
	t_material m;

	s = shape_create();
	s = shape_set_transform(s, translation(2, 3, 4));
	TEST_ASSERT(mat_equal(s.transform, translation(2, 3, 4)),
		"shape transform set correctly");
	m = material_create();
	m.ambient = 1.0;
	s = shape_set_material(s, m);
	TEST_ASSERT(material_equal(s.material, m),
		"shape material set correctly");
}

static void	shape_normal_computation(void)
{
	t_shape	 s;
	t_tuple	 n;

	s = shape_create();
	s = shape_set_transform(s, translation(0, 1, 0));
	n = shape_normal_at(&s, point(0, 1.70711, -0.70711),
			local_normal_testshape);
	TEST_ASSERT(floats_equal(n.x, 0.0)
		&& floats_close(n.y, 0.70711, EPS, EPS)
		&& floats_close(n.z, -0.70711, EPS, EPS),
		"normal on translated shape");

	s = shape_create();
	s = shape_set_transform(s, mat_mul(scaling(1, 0.5, 1), rotation_z(M_PI/5.0)));
	n = shape_normal_at(&s, point(0, sqrt(2.0)/2.0, -sqrt(2.0)/2.0),
			local_normal_testshape);
	TEST_ASSERT(floats_equal(n.x, 0.0)
		&& floats_close(n.y, 0.97014, EPS, EPS)
		&& floats_close(n.z, -0.24254, EPS, EPS),
		"normal on transformed shape");
}

static void	plane_normal_is_constant(void)
{
	(void)plane_create();
	TEST_ASSERT(tuples_equal(plane_local_normal_at(point(0,0,0)), vector(0,1,0)),
		"plane normal at origin");
	TEST_ASSERT(tuples_equal(plane_local_normal_at(point(10,0,-10)), vector(0,1,0)),
		"plane normal far point");
	TEST_ASSERT(tuples_equal(plane_local_normal_at(point(-5,0,150)), vector(0,1,0)),
		"plane normal another point");
}

static void	plane_ray_parallel_and_coplanar(void)
{
	t_plane	p;
	t_ray	r;
	t_xs	xs;

	p = plane_create();
	r = ray(point(0, 10, 0), vector(0, 0, 1));
	xs = plane_local_intersect(&p, r);
	TEST_ASSERT(xs.count == 0, "parallel ray misses plane");

	r = ray(point(0, 0, 0), vector(0, 0, 1));
	xs = plane_local_intersect(&p, r);
	TEST_ASSERT(xs.count == 0, "coplanar ray returns empty");
}

static void	plane_ray_hits_from_above_below(void)
{
	t_plane	p;
	t_ray	r;
	t_xs	xs;

	p = plane_create();
	r = ray(point(0, 1, 0), vector(0, -1, 0));
	xs = plane_local_intersect(&p, r);
	TEST_ASSERT(xs.count == 1, "ray from above hits once");
	TEST_ASSERT(fabs(xs.intersections[0].t - 1.0) < EPS,
		"hit t == 1");
	TEST_ASSERT(xs.intersections[0].object == &p, "hit object is plane");

	r = ray(point(0, -1, 0), vector(0, 1, 0));
	xs = plane_local_intersect(&p, r);
	TEST_ASSERT(xs.count == 1, "ray from below hits once");
	TEST_ASSERT(fabs(xs.intersections[0].t - 1.0) < EPS,
		"hit t == 1");
	TEST_ASSERT(xs.intersections[0].object == &p, "hit object is plane");
}

void	run_chapter9_tests(void)
{
	printf("\n=== Chapter 9: Planes & Shapes ===\n");
	shape_default_transform_material();
	shape_assign_transform_material();
	shape_ray_saved_after_transform();
	shape_ray_saved_after_translation();
	shape_normal_computation();
	plane_normal_is_constant();
	plane_ray_parallel_and_coplanar();
	plane_ray_hits_from_above_below();
	printf("\n=== Chapter 9 Tests Complete ===\n\n");
}

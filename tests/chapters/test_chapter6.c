#include "../test_common.h"
#include <math.h>

static void	assert_color_close(t_tuple color, double r, double g, double b,
		const char *message)
{
	int	pass;

	pass = floats_close(color.x, r, EPS, EPS)
		&& floats_close(color.y, g, EPS, EPS)
		&& floats_close(color.z, b, EPS, EPS);
	TEST_ASSERT(pass, message);
}

static t_tuple	lighting_call(t_material m, t_point_light light,
			t_tuple position, t_tuple eyev, t_tuple normalv)
{
	t_lighting_args	args;

	args.material = m;
	args.light = light;
	args.position = position;
	args.eyev = eyev;
	args.normalv = normalv;
	return (lighting(args));
}

void	test_ch6_normal_on_x_axis(void)
{
	t_sphere	s;
	t_tuple		n;

	printf("Chapter 6: Normal on sphere at x axis\n");
	s = sphere_create();
	n = sphere_normal_at(&s, point(1, 0, 0));
	TEST_ASSERT(tuples_equal(n, vector(1, 0, 0)),
		"n = vector(1, 0, 0)");
}

void	test_ch6_normal_on_y_axis(void)
{
	t_sphere	s;
	t_tuple		n;

	printf("Chapter 6: Normal on sphere at y axis\n");
	s = sphere_create();
	n = sphere_normal_at(&s, point(0, 1, 0));
	TEST_ASSERT(tuples_equal(n, vector(0, 1, 0)),
		"n = vector(0, 1, 0)");
}

void	test_ch6_normal_on_z_axis(void)
{
	t_sphere	s;
	t_tuple		n;

	printf("Chapter 6: Normal on sphere at z axis\n");
	s = sphere_create();
	n = sphere_normal_at(&s, point(0, 0, 1));
	TEST_ASSERT(tuples_equal(n, vector(0, 0, 1)),
		"n = vector(0, 0, 1)");
}

void	test_ch6_normal_on_nonaxial_point(void)
{
	t_sphere	s;
	t_tuple		n;
	double		inv_sqrt3;

	printf("Chapter 6: Normal on sphere at nonaxial point\n");
	s = sphere_create();
	inv_sqrt3 = sqrt(3.0) / 3.0;
	n = sphere_normal_at(&s, point(inv_sqrt3, inv_sqrt3, inv_sqrt3));
	TEST_ASSERT(tuples_equal(n, vector(inv_sqrt3, inv_sqrt3, inv_sqrt3)),
		"n = vector(√3/3, √3/3, √3/3)");
}

void	test_ch6_normal_is_normalized(void)
{
	t_sphere	s;
	t_tuple		n;
	double		inv_sqrt3;

	printf("Chapter 6: Sphere normal is normalized\n");
	s = sphere_create();
	inv_sqrt3 = sqrt(3.0) / 3.0;
	n = sphere_normal_at(&s, point(inv_sqrt3, inv_sqrt3, inv_sqrt3));
	TEST_ASSERT(tuples_equal(n, normalize_vector(n)),
		"n = normalize(n)");
}

void	test_ch6_normal_on_translated_sphere(void)
{
	t_sphere	s;
	t_tuple		n;

	printf("Chapter 6: Normal on translated sphere\n");
	s = sphere_create();
	s = sphere_set_transform(s, translation(0, 1, 0));
	n = sphere_normal_at(&s, point(0, 1.70711, -0.70711));
	TEST_ASSERT(floats_equal(n.x, 0.0)
		&& floats_close(n.y, 0.70711, EPS, EPS)
		&& floats_close(n.z, -0.70711, EPS, EPS),
		"n = vector(0, 0.70711, -0.70711)");
}

void	test_ch6_normal_on_transformed_sphere(void)
{
	t_sphere	s;
	t_tuple		n;
	t_matrix	m;

	printf("Chapter 6: Normal on rotated/scaled sphere\n");
	s = sphere_create();
	m = mat_mul(scaling(1, 0.5, 1), rotation_z(M_PI / 5.0));
	s = sphere_set_transform(s, m);
	n = sphere_normal_at(&s, point(0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0));
	TEST_ASSERT(floats_equal(n.x, 0.0)
		&& floats_close(n.y, 0.97014, EPS, EPS)
		&& floats_close(n.z, -0.24254, EPS, EPS),
		"n = vector(0, 0.97014, -0.24254)");
}

void	test_ch6_reflect_vector_45(void)
{
	t_tuple	v;
	t_tuple	n;
	t_tuple	r;

	printf("Chapter 6: Reflect vector approaching at 45°\n");
	v = vector(1, -1, 0);
	n = vector(0, 1, 0);
	r = reflect(v, n);
	TEST_ASSERT(tuples_equal(r, vector(1, 1, 0)),
		"r = vector(1, 1, 0)");
}

void	test_ch6_reflect_vector_slanted_surface(void)
{
	t_tuple	v;
	t_tuple	n;
	t_tuple	r;
	double		inv_sqrt2;

	printf("Chapter 6: Reflect vector off slanted surface\n");
	inv_sqrt2 = sqrt(2.0) / 2.0;
	v = vector(0, -1, 0);
	n = vector(inv_sqrt2, inv_sqrt2, 0);
	r = reflect(v, n);
	TEST_ASSERT(tuples_equal(r, vector(1, 0, 0)),
		"r = vector(1, 0, 0)");
}

void	test_ch6_point_light_attributes(void)
{
	t_tuple		intensity;
	t_tuple		position;
	t_point_light	light;

	printf("Chapter 6: Point light has position and intensity\n");
	intensity = color_d(1, 1, 1);
	position = point(0, 0, 0);
	light = point_light(position, intensity);
	TEST_ASSERT(tuples_equal(light.position, position),
		"light.position = position");
	TEST_ASSERT(tuples_equal(light.intensity, intensity),
		"light.intensity = intensity");
}

void	test_ch6_default_material(void)
{
	t_material	m;

	printf("Chapter 6: Default material values\n");
	m = material_create();
	TEST_ASSERT(tuples_equal(m.color, color_d(1, 1, 1)),
		"m.color = color(1, 1, 1)");
	TEST_ASSERT(floats_equal(m.ambient, 0.1), "m.ambient = 0.1");
	TEST_ASSERT(floats_equal(m.diffuse, 0.9), "m.diffuse = 0.9");
	TEST_ASSERT(floats_equal(m.specular, 0.9), "m.specular = 0.9");
	TEST_ASSERT(floats_equal(m.shininess, 200.0), "m.shininess = 200.0");
}

void	test_ch6_sphere_has_default_material(void)
{
	t_sphere	s;

	printf("Chapter 6: Sphere has default material\n");
	s = sphere_create();
	TEST_ASSERT(tuples_equal(s.material.color, color_d(1, 1, 1)),
		"s.material = material()");
}

void	test_ch6_assign_material_to_sphere(void)
{
	t_sphere	s;
	t_material	m;

	printf("Chapter 6: Assign material to sphere\n");
	s = sphere_create();
	m = material_create();
	m.ambient = 1.0;
	s = sphere_set_material(s, m);
	TEST_ASSERT(floats_equal(s.material.ambient, 1.0),
		"s.material = m");
}

void	test_ch6_lighting_eye_between_light_and_surface(void)
{
	t_material	m;
	t_tuple	position;
	t_tuple	result;

	printf("Chapter 6: Lighting eye between light and surface\n");
	m = material_create();
	position = point(0, 0, 0);
	result = lighting_call(m, point_light(point(0, 0, -10), color_d(1, 1, 1)),
		position, vector(0, 0, -1), vector(0, 0, -1));
	assert_color_close(result, 1.9, 1.9, 1.9,
		"result = color(1.9, 1.9, 1.9)");
}

void	test_ch6_lighting_eye_offset_45(void)
{
	t_material	m;
	t_tuple	position;
	t_tuple	result;
	double		inv_sqrt2;

	printf("Chapter 6: Lighting eye offset 45°\n");
	m = material_create();
	position = point(0, 0, 0);
	inv_sqrt2 = sqrt(2.0) / 2.0;
	result = lighting_call(m, point_light(point(0, 0, -10), color_d(1, 1, 1)),
		position, vector(0, inv_sqrt2, -inv_sqrt2), vector(0, 0, -1));
	assert_color_close(result, 1.0, 1.0, 1.0,
		"result = color(1.0, 1.0, 1.0)");
}

void	test_ch6_lighting_light_offset_45(void)
{
	t_material	m;
	t_tuple	position;
	t_tuple	result;

	printf("Chapter 6: Lighting with light offset 45°\n");
	m = material_create();
	position = point(0, 0, 0);
	result = lighting_call(m, point_light(point(0, 10, -10),
		color_d(1, 1, 1)), position, vector(0, 0, -1), vector(0, 0, -1));
	assert_color_close(result, 0.7364, 0.7364, 0.7364,
		"result = color(0.7364, 0.7364, 0.7364)");
}

void	test_ch6_lighting_eye_in_path_of_reflection(void)
{
	t_material	m;
	t_tuple	position;
	t_tuple	result;
	double		inv_sqrt2;

	printf("Chapter 6: Lighting eye in path of reflection\n");
	m = material_create();
	position = point(0, 0, 0);
	inv_sqrt2 = sqrt(2.0) / 2.0;
	result = lighting_call(m, point_light(point(0, 10, -10),
		color_d(1, 1, 1)), position, vector(0, -inv_sqrt2, -inv_sqrt2),
		vector(0, 0, -1));
	assert_color_close(result, 1.6364, 1.6364, 1.6364,
		"result = color(1.6364, 1.6364, 1.6364)");
}

void	test_ch6_lighting_light_behind_surface(void)
{
	t_material	m;
	t_tuple	position;
	t_tuple	result;

	printf("Chapter 6: Lighting light behind surface\n");
	m = material_create();
	position = point(0, 0, 0);
	result = lighting_call(m, point_light(point(0, 0, 10), color_d(1, 1, 1)),
		position, vector(0, 0, -1), vector(0, 0, -1));
	assert_color_close(result, 0.1, 0.1, 0.1,
		"result = color(0.1, 0.1, 0.1)");
}

void	run_chapter6_tests(void)
{
	test_ch6_normal_on_x_axis();
	test_ch6_normal_on_y_axis();
	test_ch6_normal_on_z_axis();
	test_ch6_normal_on_nonaxial_point();
	test_ch6_normal_is_normalized();
	test_ch6_normal_on_translated_sphere();
	test_ch6_normal_on_transformed_sphere();
	test_ch6_reflect_vector_45();
	test_ch6_reflect_vector_slanted_surface();
	test_ch6_point_light_attributes();
	test_ch6_default_material();
	test_ch6_sphere_has_default_material();
	test_ch6_assign_material_to_sphere();
	test_ch6_lighting_eye_between_light_and_surface();
	test_ch6_lighting_eye_offset_45();
	test_ch6_lighting_light_offset_45();
	test_ch6_lighting_eye_in_path_of_reflection();
	test_ch6_lighting_light_behind_surface();
}

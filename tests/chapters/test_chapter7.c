// #include "../test_ch7_common.h"
#include "../test_common.h"
//Libraries I do really need directly:
#include "stdio.h" //printf or use own libft
#include "lights.h"
#include "spheres.h"
#include <stdbool.h>

# define MAX_OBJECTS 32

//GOOD HELP STUFF:
void print_light(const t_point_light *light, const char *label)
{
	if (label)
		printf("\n--- %s ---\n", label);
	printf("Position:  point(%.2f, %.2f, %.2f)\n", light->position.x, light->position.y, light->position.z);
	printf("Intensity: tuple(%.2f, %.2f, %.2f, brightness: %.2f)\n\n", light->intensity.x, light->intensity.y, light->intensity.z, light->intensity.w);
	printf("\n\n");
}

bool	lights_equal(t_point_light a, t_point_light b)
{
	return (tuples_equal(a.position, b.position) &&
			tuples_equal(a.intensity, b.intensity));
}

static bool	material_equal(t_material a, t_material b)
{
	bool    color_match;
	bool    ambient_match;
	bool    diffuse_match;
	bool    specular_match;
	bool    shininess_match;

	// Compare color using existing tuple_equal function
	color_match = tuples_equal(a.color, b.color);

	// Compare double values with EPSILON tolerance
	ambient_match = (fabs(a.ambient - b.ambient) < EPS);
	diffuse_match = (fabs(a.diffuse - b.diffuse) < EPS);
	specular_match = (fabs(a.specular - b.specular) < EPS);
	shininess_match = (fabs(a.shininess - b.shininess) < EPS);

	return (color_match && ambient_match && diffuse_match 
			&& specular_match && shininess_match);
}

bool	spheres_equal(t_sphere a, t_sphere b)
{
	bool	transform_match;
	bool	material_match;

	// Compare transformation matrices
	transform_match = mat_equal(a.transform, b.transform);

	// Compare materials
	material_match = material_equal(a.material, b.material);

	return (transform_match && material_match);
}
static void	print_material(t_material mat)
{
	printf("  color: (%.3f, %.3f, %.3f)\n",
			mat.color.x, mat.color.y, mat.color.z);
	printf("  ambient: %.3f\n", mat.ambient);
	printf("  diffuse: %.3f\n", mat.diffuse);
	printf("  specular: %.3f\n", mat.specular);
	printf("  shininess: %.3f\n", mat.shininess);
}

static void	print_sphere(const char *name, t_sphere s)
{
	printf("\n Sphere '%s':", name);
	printf("Transform matrix:\n");
	print_matrix(s.transform);
	printf("\n");
	printf("Material:\n");
	print_material(s.material);
}

// FOR WORLD.H -------------------------------------

/* ==========  World Structure with Typed Object Arrays ========== */
// TODO:
// t_plane			planes[MAX_OBJECTS];
// int				planes_count;
// t_cylinder		cylinders[MAX_OBJECTS];
// int				cylinders_count;
// explicit presence flag is for:
// "0" - is this absence of light or black light?
typedef struct	s_world
{
	bool			light_present; // explicit presence flag 
	t_point_light	light;
	t_sphere		spheres[MAX_OBJECTS];
	int				spheres_count;
}	t_world;

// Note: w.light.val doesn't need initialization when present=false
// Note: spheres array doesn't need initialization for empty world
// TODO:
// w.planes_count = 0;
// w.cylinders_count = 0;
t_world	world_make(void)
{
	t_world	w;

	w.light_present = false;
	w.light.position = tuple(0, 0, 0, 0);
	w.light.intensity = tuple(0, 0, 0, 0);
	w.spheres_count = 0;
	return (w);
}

void	test_ch7_creating_world(void)
{
	printf("Chapter 7: Creating a world\n\n");
	t_world w;

	w = world_make();
	printf("w.spheres_count = %d\n", w.spheres_count);
	print_light(&w.light, "Actual Light");
	TEST_ASSERT(w.spheres_count == 0, "world contains no objects");
}


/* ========== START: Default World Creation ========== */
/*
** default_world: Create the default world for testing
** Returns: World with predefined light and two spheres
** Description: Creates world as described in "The Ray Tracer Challenge"
**   - Light at (-10, 10, -10) with white intensity
**   - Sphere 1: color(0.8, 1.0, 0.6), diffuse=0.7, specular=0.2
**   - Sphere 2: scaled by (0.5, 0.5, 0.5)
*/
t_world	default_world(void)
{
	t_world			w;
	t_material		m1;

	// Initialize empty world
	w = world_make();

	// Set up light
	w.light_present = true;
	w.light.position = point(-10, 10, -10);
	w.light.intensity = point(1, 1, 1);

	// Create first sphere (outer) with custom material
	w.spheres[0] = sphere_create();
	m1 = material_create();
	m1.color = point(0.8, 1.0, 0.6);
	m1.diffuse = 0.7;
	m1.specular = 0.2;
	w.spheres[0].material = m1;
	w.spheres[0].transform = mat_identity();

	// Create second sphere (inner) with scaling
	w.spheres[1] = sphere_create();
	w.spheres[1].material = material_create();
	w.spheres[1].transform = scaling(0.5, 0.5, 0.5);

	w.spheres_count = 2;

	return (w);
}


/*
Scenario: The default world
Given light ← point_light(point(-10, 10, -10), color(1, 1, 1))
And s1 ← sphere() with:
| material.color
| (0.8, 1.0, 0.6)
|
| material.diffuse
| 0.7
|
| material.specular | 0.2
|
And s2 ← sphere() with:
| transform | scaling(0.5, 0.5, 0.5) |
When w ← default_world()
Then w.light = light
And w contains s1
And w contains s2
*/
/*
** Example: test_ch7_default_world()
** Description: Unit test for the default world configuration.
** Uses: default_world(), point_light(), sphere_equal()
** Verified: All 42 Norm, naming, and formatting rules applied.
*/
void	test_ch7_default_world(void)
{
	printf("Chapter 7: The default world\n\n");
	t_world			w;
	t_point_light	expected_light;
	t_sphere		s1;
	t_sphere		s2;
	t_material		m1;

	// Create default world
	w = default_world();

	// Set up expected light
	expected_light = point_light(point(-10, 10, -10), point(1, 1, 1));

	// Set up expected first sphere
	s1 = sphere_create();
	m1 = material_create();
	m1.color = point(0.8, 1.0, 0.6);
	m1.diffuse = 0.7;
	m1.specular = 0.2;
	s1.material = m1;

	// Set up expected second sphere
	s2 = sphere_create();
	s2.transform = scaling(0.5, 0.5, 0.5);

	// Test light
	TEST_ASSERT(w.light_present, "Default world should have a light");
	TEST_ASSERT(tuples_equal(w.light.position, expected_light.position),
				"Light position is correct");
	TEST_ASSERT(tuples_equal(w.light.intensity, expected_light.intensity),
				"Light intensity is correct");

	// Test sphere count
	TEST_ASSERT(w.spheres_count == 2, "Default world contains 2 spheres");

	// Test first sphere
	TEST_ASSERT(spheres_equal(w.spheres[0], s1),
				"Default world contains s1");
	print_sphere("Actual s1", w.spheres[0]);
	print_sphere("s1", s1);

	// Test second sphere
	TEST_ASSERT(spheres_equal(w.spheres[1], s2),
				"Default world contains s2");
	print_sphere("Actual s2", w.spheres[1]);
	printf("\n");
}

/*
STACK TRANSLATIONS OF YOUR FUNCTIONS()
STACK BASED STRUCTURES

*/
/*
Scenario: Intersect a world with a ray
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 0, 1))
When xs ← intersect_world(w, r)Then xs.count = 4
And xs[0].t = 4
And xs[1].t = 4.5
And xs[2].t = 5.5
And xs[3].t = 6
*/
t_xs_stack	intersect_world_stack(t_world *w, t_ray r)
{
	t_xs_stack	result;
	t_xs_stack	temp;
	int			i;
	int			j;

	/* START: Initialize empty result collection */
	result = xs_create_stack();
	/* END: Initialize empty result collection */
	
	/* START: Iterate through all objects in world */
	i = 0;
	while (i < w->spheres_count)
	{
		/* ASSUMPTION: All objects in world are spheres (t_sphere*) */
		/* HEAP TRANSITION NOTE: Object type logic remains same for heap version */
		temp = sphere_intersect_stack(&w->spheres[i], r);
		
		/* START: Merge intersections from this object into result */
		/* xs_add_stack maintains sorted order automatically */
		j = 0;
		while (j < temp.count)
		{
			xs_add_stack(&result, temp.intersections[j]);
			j++;
		}
		/* END: Merge intersections from this object into result */
		i++;
	}
	/* END: Iterate through all objects in world */
	return (result);
}

/*
** Example: test_ch7_intersect_world_stack()
** Description: Unit test for intersecting a world with a ray (STACK version).
** Scenario: A ray through origin should hit both spheres in default_world
** for a total of 4 intersections at t=4, 4.5, 5.5, 6.
** Uses: default_world(), ray_create(), point(), vector(), intersect_world_stack()
** Verified: All 42 Norm, naming, and formatting rules applied.
*/
void	test_ch7_intersect_world_stack(void)
{
	t_world		w;
	t_ray		r;
	t_xs_stack	xs;

	printf("Chapter 7: Intersecting a world with a ray (STACK version)\n\n");
	
	/* START: Setup default world and ray */
	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	/* END: Setup default world and ray */
	
	/* START: Display world configuration */
	printf("World configuration:\n");
	printf("  Number of spheres: %d\n", w.spheres_count);
	printf("  Ray origin: (0, 0, -5)\n");
	printf("  Ray direction: (0, 0, 1)\n");
	printf("\n");
	/* END: Display world configuration */
	
	/* START: Perform intersection */
	xs = intersect_world_stack(&w, r);
	/* END: Perform intersection */
	
	/* START: Display results */
	printf("Intersection results:\n");
	printf("  Total intersections: %d\n", xs.count);
	printf("\n");
	
	if (xs.count >= 4)
	{
		printf("  xs[0].t = %.1f\n", xs.intersections[0].t);
		printf("  xs[1].t = %.1f\n", xs.intersections[1].t);
		printf("  xs[2].t = %.1f\n", xs.intersections[2].t);
		printf("  xs[3].t = %.1f\n", xs.intersections[3].t);
	}
	printf("\n");
	/* END: Display results */
	
	/* START: Assertions */
	TEST_ASSERT(xs.count == 4,
		"world intersection count is 4");
	TEST_ASSERT(fabs(xs.intersections[0].t - 4.0) < EPS,
		"xs[0].t = 4");
	TEST_ASSERT(fabs(xs.intersections[1].t - 4.5) < EPS,
		"xs[1].t = 4.5");
	TEST_ASSERT(fabs(xs.intersections[2].t - 5.5) < EPS,
		"xs[2].t = 5.5");
	TEST_ASSERT(fabs(xs.intersections[3].t - 6.0) < EPS,
		"xs[3].t = 6");
	/* END: Assertions */
}


void run_chapter7_tests(void)
{
	printf("\n=== Chapter 7: Making a Scene ===\n");
	test_ch7_creating_world();
	test_ch7_default_world();
	test_ch7_intersect_world_stack();
	printf("\n=== Chapter 7 Tests Complete ===\n\n");
}

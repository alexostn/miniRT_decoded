#include "../test_ch7_common.h"

/*
** =============================================================================
** ==                   Standalone Test for Chapter 7                         ==
** =============================================================================
**
** Description:
**   This file is self-contained to avoid header/dependency hell.
**   It uses a STACK-BASED approach with local type definitions.
**
** =============================================================================
*/
//GOOD HELP STUFF:
static void print_light(const t_point_light *light, const char *label)
{
	if (label)
		printf("--- %s ---\n", label);
	printf("Position:  point(%.2f, %.2f, %.2f)\n", light->position.x, light->position.y, light->position.z);
	printf("Intensity: tuple(%.2f, %.2f, %.2f, brightness: %.2f)\n\n", light->intensity.x, light->intensity.y, light->intensity.z, light->intensity.w);
	printf("\n\n");
}
// --- Local Type Definitions (Private to this file) TODO in objects.h/*c---

typedef struct s_material
{
	t_tuple color;
	double  ambient, diffuse, specular, shininess;
} t_material;

typedef struct s_object
{
	t_matrix	transform;
	t_material	material;
} t_object;

// --- Local Type Definitions STACK-BASED (Private to this file) TODO in world.h/*c---
#define MAX_OBJECTS 10

typedef struct s_opt_light { bool present; t_light val; } t_opt_light;
typedef struct s_world
{
	t_opt_light	light;		// Optional light source	
	t_object	objects[MAX_OBJECTS];
	int			count;		// Current number of objects
}	t_world;

static t_world	world_make(void)
{
	t_world	w;

	w.light.present = false;
	w.count = 0;
	return (w);
}

// --- Local Stub Functions & Helpers ---

static bool	light_equal(t_light a, t_light b)
{
	return (tuples_equal(a.position, b.position) &&
			color_equal(a.intensity, b.intensity));
}

static bool material_equal(t_material a, t_material b) { return (tuples_equal(a.color, b.color) && floats_equal(a.diffuse, b.diffuse) && floats_equal(a.specular, b.specular)); }
static bool object_equal(t_object a, t_object b) { return (mat_equal(a.transform, b.transform) && material_equal(a.material, b.material)); }


// Test-only object creator
static t_object sphere_make_stub(void)
{
	t_object obj;
	obj.transform = mat_identity();
	obj.material = (t_material){tuple(1,1,1,0), 0.1, 0.9, 0.9, 200.0};
	return (obj);
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
// Test-only function to create the default world on the STACK TODO in world.h/*c
static t_world create_default_world_stack(void)
{
	t_world w = world_make();
	// t_world w = {0};
	t_object s1, s2;

	w.light.val = (t_light)
	{
		point(-10, 10, -10),		// returns t_tuple for position
		color_create(1.0, 1.0, 1.0)	// returns t_color for intensity
	};
	w.light.present = true;

	s1 = sphere_make_stub();
	s1.material.color = tuple(0.8, 1.0, 0.6, 0);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;

	s2 = sphere_make_stub();
	s2.transform = scaling(0.5, 0.5, 0.5);

	w.objects[0] = s1;
	w.objects[1] = s2;
	w.count = 2;
	return (w);
}


/*
** =============================================================================
** ==                         CHAPTER 7 TESTS                                 ==
** =============================================================================
*/

void test_ch7_creating_world(void)
{
	printf("Chapter 7: Creating an empty world (stack)\n\n");
	t_world w = world_make();
	TEST_ASSERT(w.count == 0, "world contains no objects");
	TEST_ASSERT(w.light.present == false, "world has no light source");
	printf("\n");
}

void test_ch7_default_world(void)
{
	printf("Chapter 7: The default world (stack)\n\n");
	t_world w;
	t_light expected_light = (t_light){point(-10, 10, -10), color_create(1, 1, 1)};

	t_object s1 = sphere_make_stub();
	s1.material.color = tuple(0.8, 1.0, 0.6, 0);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;
	t_object s2 = sphere_make_stub();
	s2.transform = scaling(0.5, 0.5, 0.5);
	bool s1_found = false, s2_found = false;
	int i = 0;

	w = create_default_world_stack();

	TEST_ASSERT(w.light.present, "Default world should have a light");
	TEST_ASSERT(light_equal(w.light.val, expected_light), "Light data is correct");
	print_light(&w.light.val, "Actual Light");
	print_light(&expected_light, "Expected Light");
	while (i < w.count) {
		if (object_equal(w.objects[i], s1)) s1_found = true;
		if (object_equal(w.objects[i], s2)) s2_found = true;
		i++;
	}
	TEST_ASSERT(s1_found, "Default world contains s1");
	TEST_ASSERT(s2_found, "Default world contains s2");
	printf("\n");
}

/*
Scenario: Intersect a world with a ray
Given w ← default_world()
And r ← ray(point(0, 0, -5), vector(0, 0, 1))
When xs ← intersect_world(w, r)

Then xs.count = 4
And xs[0].t = 4
And xs[1].t = 4.5
And xs[2].t = 5.5
And xs[3].t = 6
*/

void run_chapter7_tests(void)
{
	printf("\n=== Chapter 7: Making a Scene ===\n");
	test_ch7_creating_world();
	test_ch7_default_world();
	printf("\n=== Chapter 7 Tests Complete ===\n\n");
}

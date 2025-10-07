#ifndef TEST_COMMON_H
# define TEST_COMMON_H

// Common includes for all test files
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <assert.h>
#include "computations.h"
#include "world.h"
#include "math_utils.h"
#include "matrices.h"
#include "transformations.h"
#include "tuples.h"
#include "projectile.h"
#include "colors.h"
#include "materials.h"
#include "lights.h"
#include "lighting.h"
#include "window.h"
#include "image.h"
#include "rays.h"
#include "spheres.h"
#include "camera.h"


// ANSI color codes for test output
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_RESET   "\x1b[0m"

// Global variables for test statistics (shared across all test files)
extern int g_tests_run;
extern int g_tests_failed;
extern char g_failed_tests[1000][100];

// Common test utility functions

// Checkers
bool	file_ends_with_newline(const char *filename);
int		is_canvas_black(t_image *canvas);

// Printing utils
void	print_tuple(t_tuple pt);
void	print_color(t_color pc);
void	print_ray(t_ray r);
void	print_intersections(t_xs xs);
void	print_matrix(t_matrix m);
void	print_light(const t_point_light *light, const char *label);
void	print_material(t_material mat);
void	print_sphere(const char *name, t_sphere s);

//Equality utils
int		compare_files(const char *f1, const char *f2);
bool	lights_equal(t_point_light a, t_point_light b);
bool	material_equal(t_material a, t_material b);
bool	spheres_equal(t_sphere a, t_sphere b);

// Override TEST_ASSERT to count tests
# undef TEST_ASSERT
# define TEST_ASSERT(condition, message) \
	do { \
		g_tests_run++; \
		printf("%-61s: ", message); \
		if (condition) { \
			printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET "\n"); \
		} else { \
			printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET "\n"); \
			if (g_tests_failed < 1000) { \
				snprintf(g_failed_tests[g_tests_failed], 100, "%s", message); \
				g_tests_failed++; \
			} \
		} \
	} while (0)

#endif

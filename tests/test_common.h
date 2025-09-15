#ifndef TEST_COMMON_H
# define TEST_COMMON_H

// Common includes for all test files
#include "math_utils.h"
#include "matrices.h"
#include "transformations.h"
#include "tuples.h"
#include "projectile.h"
#include "colors.h"
#include "window.h"
#include "image.h"
#include "rays.h"
#include "spheres.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <assert.h>

// ANSI color codes for test output
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_RESET   "\x1b[0m"

// Global variables for test statistics (shared across all test files)
extern int g_tests_run;
extern int g_tests_failed;
extern char g_failed_tests[1000][100];

// Common test utility functions
void	print_tuple(t_tuple pt);
void	print_color(t_color pc);
void	print_ray(t_ray r);
void	print_intersections(t_xs xs);
void	print_matrix(t_matrix m);
int		compare_files(const char *f1, const char *f2);
bool	file_ends_with_newline(const char *filename);
int		is_canvas_black(t_image *canvas);

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

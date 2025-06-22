#include "include/tuples.h" // Указывай путь к твоим заголовочным файлам из src/
#include "include/projectile.h" // projectile.h includes environment.h
#include "include/colors.h"
#include "include/window.h"
#include "include/image.h"
// #include "include/canvas.h" // For future chapters
// #include "include/matrices.h" // For future chapters
#include <stdio.h> // for printf
#include <fcntl.h> // for test files ppm and comparisson
#include <stdbool.h> // for file_ends_with_newline

// --- Macro for displaying test results (optional, for clarity) ---
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define TEST_ASSERT(condition, message) \
	do { \
		printf("%-61s: ", message); \
		if (condition) { \
			printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET "\n"); \
		} else { \
			printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET "\n"); \
		} \
	} while (0)

///TO HELP PRINTING:

void	print_tuple(t_tuple	pt)
{
	printf("x=%.5f, y=%.5f, z=%.5f, w=%.5f\n",
		pt.x, pt.y, pt.z, pt.w);
}

void	print_color(t_color	pc)
{
	printf("r=%.5f, g=%.5f, b=%.5f, w=%.5f\n",
		pc.r, pc.g, pc.b, pc.a);
}

#ifndef TEST_UTILS_H
# define TEST_UTILS_H


#include <stdio.h> // for printf
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

#endif
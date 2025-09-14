#include "test_common.h"

// Forward declarations for chapter test functions
void run_chapter1_tests(void);
void run_chapter2_tests(void);
void run_chapter3_tests(void);
void run_chapter4_tests(void);
void run_chapter5_tests(void);

void print_test_summary(void)
{
	printf("========================================\n");
	printf("TEST SUMMARY\n");
	printf("========================================\n");
	printf("Tests run: %d\n", g_tests_run);
	printf("Tests passed: %d\n", g_tests_run - g_tests_failed);
	printf("Tests failed: %d\n", g_tests_failed);
	printf("Success rate: %.1f%%\n", 
		100.0 * (g_tests_run - g_tests_failed) / g_tests_run);
	
	if (g_tests_failed > 0)
	{
		printf("\nFailed tests:\n");
		for (int i = 0; i < g_tests_failed; i++)
		{
			printf("  - %s\n", g_failed_tests[i]);
		}
	}
	printf("========================================\n");
}

int main(void)
{
	printf("Starting The Raytracer Challenge Book Tests\n");
	printf("========================================\n");
	
	// Initialize test counters
	g_tests_run = 0;
	g_tests_failed = 0;
	
	// Run all chapter tests in order
	run_chapter1_tests();
	run_chapter2_tests();
	run_chapter3_tests();
	run_chapter4_tests();
	run_chapter5_tests();
	
	// Print final summary
	print_test_summary();
	
	printf("\n--- All book tests finished. ---\n");
	
	// Return exit code based on test results
	return (g_tests_failed > 0) ? 1 : 0;
}

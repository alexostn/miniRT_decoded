/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:00:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 23:58:11 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "test_common.h"
#include <stdio.h>

static void	test_parse_double(void)
{
	char	*test;
	char	*ptr;
	double	result;

	printf("\n=== Testing parse_double ===\n");
	test = "-50.5";
	ptr = test;
	result = parse_double(&ptr);
	printf("Test 1: parse_double(\"%s\") = %f\n", test, result);
	test = "123.456";
	ptr = test;
	result = parse_double(&ptr);
	printf("Test 2: parse_double(\"%s\") = %f\n", test, result);
	test = "-0.1";
	ptr = test;
	result = parse_double(&ptr);
	printf("Test 3: parse_double(\"%s\") = %f\n", test, result);
}

static void	test_parse_color_rgb(void)
{
	char	*test;
	char	*ptr;
	t_tuple	result;

	printf("\n=== Testing parse_color_rgb ===\n");
	test = "255,128,0";
	ptr = test;
	result = parse_color_rgb(&ptr);
	if (result.w == -1.0)
		printf("Test 1: parse_color_rgb(\"%s\") = ERROR\n", test);
	else
		printf("Test 1: parse_color_rgb(\"%s\") = (%.2f, %.2f, %.2f)\n",
			test, result.x, result.y, result.z);
	test = "255,300,0";
	ptr = test;
	result = parse_color_rgb(&ptr);
	if (result.w == -1.0)
		printf("Test 2: parse_color_rgb(\"%s\") = ERROR (correctly rejected)\n",
			test);
	else
		printf("Test 2: parse_color_rgb(\"%s\") = (%.2f, %.2f, %.2f)\n",
			test, result.x, result.y, result.z);
	test = "0,0,256";
	ptr = test;
	result = parse_color_rgb(&ptr);
	if (result.w == -1.0)
		printf("Test 3: parse_color_rgb(\"%s\") = ERROR (correctly rejected)\n",
			test);
	else
		printf("Test 3: parse_color_rgb(\"%s\") = (%.2f, %.2f, %.2f)\n",
			test, result.x, result.y, result.z);
}

static void	test_parse_vector3(void)
{
	char	*test;
	char	*ptr;
	t_tuple	result;

	printf("\n=== Testing parse_vector3 ===\n");
	test = "-50,0,20";
	ptr = test;
	result = parse_vector3(&ptr);
	printf("Test: parse_vector3(\"%s\") = (%.2f, %.2f, %.2f)\n",
		test, result.x, result.y, result.z);
}

int	main(void)
{
	printf("========================================\n");
	printf("  miniRT Parser Unit Tests\n");
	printf("========================================\n");
	test_parse_double();
	test_parse_vector3();
	test_parse_color_rgb();
	printf("\n========================================\n");
	printf("✓ All parser unit tests completed!\n");
	printf("========================================\n");
	return (0);
}

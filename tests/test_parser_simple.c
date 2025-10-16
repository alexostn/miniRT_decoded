/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_simple.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:33:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 23:35:30 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	main(void)
{
	t_scene	scene;

	printf("========================================\n");
	printf("  miniRT Parser Test\n");
	printf("========================================\n\n");
	printf("Testing parser with: ../scenes/test.rt\n\n");
	scene = parse_scene_file("../scenes/test.rt");
	printf("✓ Parsing completed successfully!\n\n");
	printf("--- Parsed Scene Data ---\n");
	printf("Ambient ratio: %.2f\n", scene.ambient_ratio);
	printf("Ambient color: (%.2f, %.2f, %.2f)\n",
		scene.ambient_color.x, scene.ambient_color.y, scene.ambient_color.z);
	printf("Camera FOV: %.2f radians\n", scene.camera.field_of_view);
	printf("Light position: (%.2f, %.2f, %.2f)\n",
		scene.world.light.position.x,
		scene.world.light.position.y,
		scene.world.light.position.z);
	printf("Sphere count: %d\n", scene.world.spheres_count);
	printf("\n✓ All tests passed!\n");
	printf("========================================\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:57:34 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/03 00:16:37 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

int	main(void)
{
	t_vars	vars;
	t_scene	scene;

	init_scene(&scene);  // Initializing the scene structure
	vars.scene = &scene; // Linking the scene to the window
	
	if (init_window(&vars))
		return (1);

	// For other miniRT logic

	// Start event processing loop
	mlx_loop(vars.mlx);

	// This code will never execute under normal circumstances,
	// as program exits via exit() in handlers
	return (0);
}

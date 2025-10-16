/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:57:34 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 19:40:51 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "minirt.h"

int	main(void)
{
	t_vars	vars;
	t_scene	scene;
	
	init_scene(&scene);
	vars.scene = &scene;
	if (init_window(&vars))
	return (1);
	mlx_loop(vars.mlx);
	return (0);
}

/*
STACK VERSION (current):
- t_scene lives on stack in main()
- vars.scene points to stack-allocated scene
- Scene auto-freed when main() returns

** Current flow:
** 1. Create scene on stack
** 2. Initialize with defaults (init_scene)
** 3. Open window and link scene
** 4. Start event loop
** 5. Scene auto-freed on exit

return (0);// Never reached (exit via close_window)

HEAP TRANSITION NOTE:
When switching to heap-based world:
1. Call scene_create() instead of init_scene()
2. Add scene_destroy() before return
3. Update close_window() to call scene_destroy()
*/
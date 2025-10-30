/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:28:06 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 04:00:46 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "window.h"
#include "defines.h"

/*
** init_window - Initialize MLX connection and create window
** @vars: Pointer to window variables structure
**
** Description:
** - Initialize connection to graphics system via mlx_init()
** - Create window with WIN_WIDTH x WIN_HEIGHT dimensions
** - Register event handlers:
**   * ESC key (keycode 65307) to close window
**   * Red cross (X button) to close window
**
** Returns: 0 on success, 1 on failure
*/
int	init_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (1);
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!vars->win)
	{
		free(vars->mlx);
		return (1);
	}
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	return (0);
}

/*
** key_hook - Handle keyboard events
** @keycode: Key code from MLX
** @vars: Pointer to window variables structure
**
** Description: ESC key (65307) closes window and exits program
** Returns: 0 (required by MLX)
*/
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		if (vars->image)
			image_destroy(vars->image);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

/*
** close_window - Handle window close event (red cross)
** @vars: Pointer to window variables structure
**
** Description: Destroys window and exits program cleanly
** Returns: 0 (never reached due to exit)
*/
int	close_window(t_vars *vars)
{
	if (vars->image)
		image_destroy(vars->image);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

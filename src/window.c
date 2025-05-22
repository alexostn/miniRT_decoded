/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:28:06 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/22 15:28:07 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

int	init_window(t_vars *vars)
{
	// Initialize connection to graphics system
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (1);

	// Create 800x600 window with title "miniRT"
	vars->win = mlx_new_window(vars->mlx, 800, 600, "miniRT");
	if (!vars->win)
	{
		free(vars->mlx);
		return (1);
	}

	// Register event handlers
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

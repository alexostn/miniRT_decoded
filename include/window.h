/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:35:28 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/16 19:34:05 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"
# include "image.h"
# include "scene.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_scene	*scene;
	t_image	*image;
}	t_vars;

int	init_window(t_vars *vars);
int	key_hook(int keycode, t_vars *vars);
int	close_window(t_vars *vars);

#endif

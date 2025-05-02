/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:35:28 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/03 00:39:49 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"
# include "minirt.h"  // Основные определения
# include <stdlib.h> // Добавлено для free() и exit()

typedef struct s_vars {
    void *mlx;
    void *win;
    t_scene *scene;
} t_vars;

int init_window(t_vars *vars);
int key_hook(int keycode, t_vars *vars);
int close_window(t_vars *vars);

#endif

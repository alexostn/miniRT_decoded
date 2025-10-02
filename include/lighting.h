/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:07:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/02 23:36:51 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "materials.h"
# include "lights.h"
# include "spheres.h"
# include "world.h"

typedef struct s_lighting_args
{
	t_material		material;
	t_point_light	light;
	t_tuple			position;
	t_tuple			eyev;
	t_tuple			normalv;
}	t_lighting_args;

struct s_light_calc
{
	t_tuple	effective_color;
	t_tuple	lightv;
	double	light_dot_normal;
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
};

t_tuple	lighting(t_lighting_args args);

#endif

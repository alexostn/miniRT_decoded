/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:05:00 by sarherna          #+#    #+#             */
/*   Updated: 2025/10/02 18:05:15 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "tuples.h"

typedef struct s_material
{
	t_tuple		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
}	t_material;

t_material	material_create(void);

#endif

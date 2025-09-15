/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:56:10 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/22 22:06:40 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "tuples.h"

typedef struct s_environmen
{
	t_tuple	gravity;
	t_tuple	wind;
}	t_environment;

t_environment	environment_create(t_tuple gravity, t_tuple wind);

#endif

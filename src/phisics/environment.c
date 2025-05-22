/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:47:24 by oostapen          #+#    #+#             */
/*   Updated: 2025/05/22 22:03:15 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_environment	environment_create(t_tuple gravity, t_tuple wind)
{
	return (t_environment){gravity, wind};
}

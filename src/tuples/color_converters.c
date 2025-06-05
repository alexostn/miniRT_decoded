/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_converters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:44:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/06/05 15:59:45 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

t_color	tuple_to_color(t_tuple tuple)
{
	return ((t_color){tuple.x, tuple.y, tuple.z, 0.0});
}

t_tuple	color_to_tuple(t_color color)
{
	return (tuple(color.r, color.g, color.b, color.a));
}

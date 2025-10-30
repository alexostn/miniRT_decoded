/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cone.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 03:10:00 by alex              #+#    #+#             */
/*   Updated: 2025/10/27 03:10:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CONE_H
# define PARSER_CONE_H

# include "parser.h"
# include "cones.h"

typedef struct s_cone_input
{
	t_tuple	center;
	t_tuple	axis;
	t_tuple	color;
	double	diameter;
	double	height;
}	t_cone_input;

t_cone_input	cone_parse_input(char *line, t_parse_state *state);
bool			cone_build_transform(t_cone_input input, t_matrix *out);
void			cone_apply_properties(t_cone *cone, t_cone_input input);

#endif

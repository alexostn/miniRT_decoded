/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_numbers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:37:13 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/26 20:37:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_NUMBERS_H
# define PARSER_NUMBERS_H

# include <stdbool.h>
# include "tuples.h"

bool	parse_double(char **str, double *val);
bool	parse_vector3(char **str, t_tuple *vec);

#endif

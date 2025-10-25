/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_numbers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 05:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/10/25 05:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_NUMBERS_H
# define PARSER_NUMBERS_H

# include <stdbool.h>
# include "tuples.h"

bool	parse_double(char **str, double *val);
bool	parse_vector3(char **str, t_tuple *vec);

#endif

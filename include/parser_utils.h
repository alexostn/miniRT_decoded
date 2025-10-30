/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:28:39 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/26 20:34:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include <stdbool.h>
# include "defines.h"
# include "tuples.h"
# include "matrices.h"

bool	build_orientation_matrix(t_tuple direction, t_matrix *out);

#endif

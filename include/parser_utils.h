/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 05:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/10/25 05:00:00 by codex            ###   ########.fr       */
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

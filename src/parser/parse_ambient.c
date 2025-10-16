/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:05:51 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/17 00:13:08 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** A 0.2 255,255,255
**   ^   ^   ^
**   |   |   +-- RGB color (0-255 each)
**   |   +------ ambient ratio (0.0-1.0)
**   +---------- identifier
*/
bool	parse_ambient(char *line, t_scene *scene)
{
	char	*ptr;
	double	ratio;
	t_tuple	color;

	ptr = line + 1;                         /* Skip 'A' */
	while (*ptr == ' ' || *ptr == '\t')     /* Skip whitespace */
		ptr++;
	ratio = parse_double(&ptr);             /* Parse ratio */
	if (ratio < 0.0 || ratio > 1.0)         /* Validate range */
		return (false);
	while (*ptr == ' ' || *ptr == '\t')     /* Skip whitespace */
		ptr++;
	color = parse_color_rgb(&ptr);          /* Parse RGB */
	if (color.x < 0)                        /* Check for error (parse_color returns -1 on fail) */
		return (false);
	scene->ambient_ratio = ratio;           /* Store values */
	scene->ambient_color = color;
	return (true);
}

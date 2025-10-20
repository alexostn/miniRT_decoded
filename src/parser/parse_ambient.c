/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:05:51 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/20 23:10:04 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
/*
** check_end_of_line - Verify no extra arguments
*/
static bool	check_end_of_line(char *ptr)
{
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	return (*ptr == '\0' || *ptr == '\n' || *ptr == '\r');
}

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

	ptr = line + 1;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	ratio = parse_double(&ptr);
	if (ratio < 0.0 || ratio > 1.0)
		return (false);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	color = parse_color_rgb(&ptr);
	if (color.w == -1.0)
		return (false);
	if (!check_end_of_line(ptr))
		return (false);
	scene->ambient_ratio = ratio;
	scene->ambient_color = color;
	return (true);
}

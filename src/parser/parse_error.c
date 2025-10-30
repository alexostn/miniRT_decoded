/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 03:30:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/25 03:30:17 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	parser_error(const char *msg, int line_num)
{
	char	*line_str;

	ft_putstr_fd("Error\n", 2);
	if (line_num > 0)
	{
		ft_putstr_fd("Line ", 2);
		line_str = ft_itoa(line_num);
		if (line_str)
		{
			ft_putstr_fd(line_str, 2);
			ft_putstr_fd(": ", 2);
			free(line_str);
		}
	}
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

/*
** parser_error_cleanup - Error handler with memory cleanup
** Frees allocated resources before exiting
*/
void	parser_error_cleanup(t_parse_state *state, const char *msg)
{
	char	*line_str;

	if (state->current_trimmed)
		free(state->current_trimmed);
	if (state->current_line)
		free(state->current_line);
	if (state->fd >= 0)
		close(state->fd);
	ft_putstr_fd("Error\n", 2);
	if (state->line_num > 0)
	{
		ft_putstr_fd("Line ", 2);
		line_str = ft_itoa(state->line_num);
		if (line_str)
		{
			ft_putstr_fd(line_str, 2);
			ft_putstr_fd(": ", 2);
			free(line_str);
		}
	}
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

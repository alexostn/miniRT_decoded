/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:30:00 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/22 20:34:39 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts a string to a double-precision floating-point number.
** Skips leading whitespace, handles optional sign (+/-), parses integer
** and fractional parts. Sets endptr to the first character after the number.
** Returns the converted value, or 0.0 if no valid conversion is performed.
*/

#include "../../inc/libft.h"

static double	ft_parse_int_part(const char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	ft_parse_frac_part(const char **str)
{
	double	result;
	double	divisor;

	result = 0.0;
	divisor = 10.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			result += (**str - '0') / divisor;
			divisor *= 10.0;
			(*str)++;
		}
	}
	return (result);
}

static int	ft_parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

double	ft_strtod(const char *str, char **endptr)
{
	double		result;
	int			sign;
	const char	*start;

	start = str;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = ft_parse_sign(&str);
	result = ft_parse_int_part(&str);
	result += ft_parse_frac_part(&str);
	if (endptr)
	{
		if (str == start || (str == start + 1
				&& (*start == '-' || *start == '+')))
			*endptr = (char *)start;
		else
			*endptr = (char *)str;
	}
	return (result * sign);
}

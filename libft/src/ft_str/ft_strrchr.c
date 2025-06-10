/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:15:47 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
The ft_strrchr function finds the last occurrence of 'c' in 's'.
It returns a pointer to 'c' or NULL if 'c' is not found.
The integer 'c' is cast to a char for comparison.
The function iterates over 's' in reverse order.
This function is a part of the libft library.
*/
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	size_t	rev_i;
	char	cc;

	rev_i = ft_strlen(s);
	i = rev_i - 1;
	cc = (char) c;
	while (i >= 0)
	{
		if (cc == s[i])
		{
			return ((char *) &s[i]);
		}
		i--;
	}
	if (cc == '\0')
		return ((char *) &s[rev_i]);
	return (NULL);
}

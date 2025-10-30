/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:11:34 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function: ft_substr (short for "substring")
 * ------------------------------------------
 * Creates a substring from the string 's'.
 * The substring starts at index 'start' and
 * is of maximum size 'len'.
 *
 * If 's' is NULL, the function returns NULL.
 *
 * If 'start' is greater than the length of 's',
 * the function returns an allocated empty string.
 *
 * If 'len' is greater than the length of the
 * substring of 's' starting at 'start', 'len'
 * is set to the length of this substring.
 *
 * Memory is allocated for the new string 'subs'
 * of size 'len + 1'. If allocation fails, the
 * function returns NULL.
 *
 * 'len' characters from 's' starting at 'start'
 * are copied into 'subs'.
 *
 * The function returns the substring 'subs'.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*subs;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	subs = ft_calloc(len + 1, sizeof(char));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:59:21 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * File: ft_strdup.c
 * ------------------
 * Includes the libft.h header file.
 *
 * Function: ft_strdup (short for "string duplicate")
 * --------------------------------------------------
 * Creates a new copy of the string 's1'.
 * Calculates the length 'l' of 's1' using ft_strlen.
 * Allocates memory for a new string 's2' of size 'l + 1'.
 * If allocation fails, returns NULL.
 * Copies 's1' into 's2' using ft_memcpy.
 * Sets the character at index 'l' of 's2' to '\0'.
 * Returns the new string 's2'.
 */
char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	l;

	l = ft_strlen(s1);
	s2 = (char *)malloc(l * sizeof(char) + 1);
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s1, l);
	s2[l] = '\0';
	return (s2);
}

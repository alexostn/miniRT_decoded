/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:48:04 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function: ft_strjoin (short for "string join")
 * ---------------------------------------------
 * Joins two strings 's1' and 's2' into a new string.
 *
 * The lengths of 's1' and 's2' are determined using 'ft_strlen'.
 *
 * If either 's1' or 's2' is NULL, the function returns NULL.
 *
 * Memory is allocated for the new string 'newstr' with a size
 * equal to the sum of the lengths of 's1' and 's2', plus one
 * for the null-terminating character.
 *
 * If memory allocation fails (i.e., 'ft_calloc' returns NULL),
 * the function returns NULL.
 *
 * The characters from 's1' and 's2' are copied into 'newstr'.
 * So, 's2[i - s1_len]' gives us the current character in 's2' that needs to be
 * copied into 'newstr'.
 * The function returns the new string 'newstr'.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*newstr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		newstr[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		newstr[i] = s2[i - s1_len];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

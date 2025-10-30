/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:36:04 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* Searches for the first occurrence of the substring
 'little' in the string 'big',
 * but does not examine more than 'len' characters in 'big'.
 * * Parameters:
 * - big: The string in which to search.
 * - little: The substring to search for.
 * - len: The maximum number of characters in 'big' to examine.
 * * Returns:
 * - If 'little' is an empty string, the function returns 'big'.
 * - If 'little' occurs in 'big' within 'len' characters,
 a pointer to the first character of the first occurrence is returned.
 * - If 'little' does not occur in 'big' within 'len' characters,
 NULL is returned.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (i + little_len <= len
			&& ft_strncmp(&big[i], little, little_len) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

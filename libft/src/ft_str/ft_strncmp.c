/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:17:05 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function: ft_strncmp (short for "string compare n characters")
 * ------------------------------------------------------------
 * Compares the first 'n' characters of two strings 's1' and 's2'.
 * Enters a loop that continues as long as either string has characters left
 * and the counter 'i' is less than 'n'.
 * Inside the loop, it compares the 'i'-th character of 's1' and 's2'.
 * The characters are cast to unsigned char to ensure that the comparison
 * is done based on the ASCII values of the characters.
 * The function will return if it finds a difference between the two strings
 * within the first 'n' characters.
 * Returns:
 * - 0, if 's1' and 's2' are equal;
 * - a negative value if 's1' is less than 's2';
 * - a positive value if 's1' is greater than 's2'.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

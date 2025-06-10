/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:12:52 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * `ft_memcmp` - "memory compare", compares `n` bytes of `s1` and `s2`.
 * 
 * Key points:
 * 1. Takes `s1`, `s2`, `n`.
 * 2. Casts `s1`, `s2` to `unsigned char` for byte comparison.
 * 3. Uses counter `i`.
 * 4. Loops while `i` is less than `n` and bytes are equal.
 * 5. Returns 0 if `n` bytes are equal.
 * 6. Otherwise, returns the difference of the first unequal bytes.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]))
		i++;
	if (i == n)
		return (0);
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

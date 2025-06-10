/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:48:38 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* memory character search
 * `ft_memchr` scans `n` bytes of `s` for `c`.
 * 
 * Key points:
 * 1. Takes `s`, `c`, and `n`.
 * 2. Casts `s` to `unsigned char` for byte comparison.
 * 3. Uses counter `i`.
 * 4. Loops while `i` is less than `n`.
 * 5. Checks if `i`th byte of `s` equals `unsigned char``c`.
 * 6. Returns pointer to matching byte or NULL.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ss;

	ss = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ss[i] == (unsigned char)c)
			return ((void *)(&ss[i]));
		i++;
	}
	return (NULL);
}

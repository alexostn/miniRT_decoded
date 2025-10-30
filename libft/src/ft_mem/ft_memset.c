/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:44:39 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function: ft_memset (short for "memory set")
 * --------------------------------------------
 * Fills the first 'n' bytes of the memory area pointed to by 's'
 * with the constant byte 'c'. Returns a pointer to the memory area 's'.
 * 'unsigned char' type ensures byte-level manipulation of the memory area.
 * Modifying memory pointed to by 'tmp_ptr' modifies 
 * the same memory pointed to by 's'.
 * Stores the byte 'c' in the memory location pointed to by 'tmp_ptr',
 * then increments 'tmp_ptr' to point to the next byte.
 * If 's' is a pointer to int array[] = {0, 1, 2, 3, 4}, 
 * function returns pointer to 0 the beginning of the array.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *) s;
	while (n > 0)
	{
		*(tmp_ptr++) = (unsigned char) c;
		n--;
	}
	return (s);
}

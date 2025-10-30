/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:09:22 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/**The ft_memcpy function copies 'n' bytes from memory area 'src' 
to memory area 'dst'.
 If 'dst' and 'src' are both NULL, it returns 'dst'.
 The 'unsigned char' type is used here to ensure byte-level
  manipulation of the memory area.
 It returns a pointer to the destination memory area 'dst'.
 `tmp_dst` and `tmp_src` are used as temporary pointers, allowing us 
 to traverse the `dest` and `src` memory areas 
 without modifying the original pointers.*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == (void *)0 && src == (void *)0)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (n > 0)
	{
		*(tmp_dst++) = *(tmp_src++);
		n--;
	}
	return (dst);
}

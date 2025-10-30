/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:48:59 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/** The ft_bzero function sets the first 'n' bytes
 of the memory area pointed to by 's' to zero.
It returns nothing as it's a void function.
 The 'unsigned char' type is used here to ensure
  byte-level manipulation of the memory area.
"store the byte `0` in the memory location currently pointed 
to by `tmp_ptr`, and then increment `tmp_ptr` to point to the next byte"*/
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *)s;
	while (n > 0)
	{
		*(tmp_ptr++) = 0;
		n--;
	}
}

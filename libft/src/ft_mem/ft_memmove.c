/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:49:45 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_d;
	unsigned char	*tmp_s;
	size_t			i;

	i = 0;
	tmp_d = (unsigned char *)dst;
	tmp_s = (unsigned char *)src;
	if (tmp_d > tmp_s)
	{
		while (n-- > 0)
			tmp_d[n] = tmp_s[n];
	}
	else
	{
		while (i < n)
		{
			tmp_d[i] = tmp_s[i];
			i++;
		}
	}
	return (dst);
}

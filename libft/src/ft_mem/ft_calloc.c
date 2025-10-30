/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:20:24 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function: ft_calloc (short for "contiguous allocation")
 one after another, without gaps
 * ------------------------------------------------------
 * Allocates memory for an array of 'count' elements,
 * each of 'size' bytes, and initializes to zero.
 * Checks for overflow in 'count' * 'size'.
 * If overflow or allocation fails, returns NULL.
 * Uses ft_memset to set allocated memory to zero.
 * Returns a pointer to the allocated memory.
 */
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;

	if (count > 0 && SIZE_MAX / count < size)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, count * size);
	return (tmp);
}

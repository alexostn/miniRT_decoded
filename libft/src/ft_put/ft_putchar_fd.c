/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:24:52 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * The `ft_putchar_fd` function writes the character `c` to the file 
 * descriptor `fd`.

 * 1. The function takes two arguments: the character `c` and the file 
 * descriptor `fd`.

 * 2. Then the `write` function is called with three arguments: the file 
 * descriptor `fd`, the address of the character `c`, and the size of the 
 * write (in this case 1, as only one character is being written).

 * 3. The `write` function writes the character `c` to the file descriptor 
 * `fd`.
 * A file descriptor is an integer identifier of an open file or other 
 * input/output resource, such as a socket or pipe.
 * input	0
 * output	1
 * error	2
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

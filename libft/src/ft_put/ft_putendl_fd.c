/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:34:39 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * The `ft_putendl_fd` function writes the string `s` to the file 
 * descriptor `fd`, and then adds a newline character (`\n`).
 *
 * Here's how it works:
 *
 * 1. The function takes two arguments: the string `s` and the file 
 * descriptor `fd`.
 *
 * 2. Then a loop starts, which continues until it reaches the end of the 
 * string `s` (i.e., until it encounters the `\0` character).
 *
 * 3. In each pass of the loop, the `write` function is called with three 
 * arguments: the file descriptor `fd`, the current character of the string 
 * `s`, and the size of the write (in this case 1, as only one character is 
 * being written).
 *
 * 4. After all the characters of the string `s` have been written, the 
 * `write` function is called one more time to write the newline character 
 * (`\n`) to the file descriptor `fd`.
 */
void	ft_putendl_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

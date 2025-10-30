/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:28:11 by oostapen          #+#    #+#             */
/*   Updated: 2025/06/10 18:25:33 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * The `ft_putstr_fd` function writes the string `s` to the file
 * descriptor `fd`.
 * It takes two arguments: the string `s` and the file descriptor `fd`.
 * If the string `s` is empty (i.e., the first character 
 * of the string is the null character), the function does nothing and 
 * returns control. 
 * Then the `write` function is called with three arguments: 
 * the file descriptor `fd`, the string `s`, and the length of the string `s` 
 * (which is returned by the `ft_strlen` function). The `write` function 
 * writes the string `s` to the file descriptor `fd`. 
 * A file descriptor is 
 * an integer identifier of an open file or other input/output resource, 
 * such as a socket or pipe. 
 * input	0
 * output	1
 * error	2
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (!*s)
		return ;
	write(fd, s, ft_strlen(s));
}

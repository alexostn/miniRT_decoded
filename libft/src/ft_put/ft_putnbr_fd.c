/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:38:47 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/02 16:05:30 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* 
 * The `ft_putnbr_fd` function writes the integer `n` to the file 
 * descriptor `fd`.
 *
 * Here's how it works:
 *
 * 1. The function takes two arguments: an integer `n` and the file 
 * descriptor `fd`.
 *
 * 2. Then the number `n` is converted to `long` and stored in the variable 
 * `nb` to avoid overflow when working with very large negative numbers.
 *
 * 3. If `nb` is less than 0, the function writes the "-" character to the 
 * file descriptor `fd` and makes `nb` positive.
 *
 * 4. If `nb` is greater than 9, the function recursively calls itself with 
 * `nb / 10`, and then writes the last digit of `nb` to the file descriptor 
 * `fd`.
 *
 * 5. If `nb` is less than or equal to 9, the function simply writes `nb` 
 * to the file descriptor `fd`.
 */
void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10) + '0', fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}
/*
#include <unistd.h>

void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putnbr(int nb) {
	if (nb < 0) {
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10) {
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10) ft_putchar(nb + 48);
}
*/

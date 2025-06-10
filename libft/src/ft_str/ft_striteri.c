/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:30:16 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * `striteri` is from "str" (string), "iter" (iterates over string), 
 * and "i" (uses an index). `f` is applied to each char of `s`.
 *
 * `ft_striteri` applies `f` to each char of `s`. 
 * It initializes a counter `i` with 0.
 * Then starts a loop that continues until the end of the string 
 * (character '\0') is reached. In each iteration, `f` is called with two 
 * arguments: the current index `i` and a pointer 
 to the current character `&s[i]`. 
 * After `f` is called, `i` is incremented by 1.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

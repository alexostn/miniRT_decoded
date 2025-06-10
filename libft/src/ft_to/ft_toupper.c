/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:22:48 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
The ft_toupper function converts a given character to uppercase
if it is lowercase.
It takes an integer 'c' as input, which should represent an ASCII character.

If the character represented by 'c' is a lowercase letter 
(ASCII values from 97 to 122), 
it is converted to its uppercase equivalent 
by subtracting 32 from its ASCII value.

If 'c' does not represent a lowercase letter, it is returned unchanged.
*/
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}

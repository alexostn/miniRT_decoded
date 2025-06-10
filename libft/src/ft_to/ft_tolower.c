/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:07:53 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
The ft_tolower function converts a given character
 to lowercase if it is uppercase.
It takes an integer 'c' as input,
 which should represent an ASCII character.

If the character represented by 'c' is an uppercase letter 
(ASCII values from 65 to 90), 
it is converted to its lowercase
 equivalent by adding 32 to its ASCII value.

If 'c' does not represent an uppercase letter, it is returned unchanged.
*/
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

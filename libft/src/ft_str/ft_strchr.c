/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:59:37 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/**
The ft_strchr function locates the first occurrence 
of character 'c' in string 's'.
It takes a string 's' and an integer 'c' as input. 
The integer 'c' is cast to a char.

The function iterates over the string 's'. If character 'c' is found,
a pointer to the character is returned.

If the character 'c' is '\0', the function returns a pointer 
to the null terminator of the string 's'.

If the character 'c' is not found in the string 's',
the function returns NULL.*/
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	cc = (char) c;
	i = 0;
	while (s[i] && s[i] != cc)
		i++;
	if (s[i] == cc)
		return ((char *) &s[i]);
	else if (cc == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

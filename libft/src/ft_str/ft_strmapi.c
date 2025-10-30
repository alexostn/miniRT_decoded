/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:50:47 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * The name `strmapi` comes from three parts: "str", "map", and "i".
 * "str" is short for string, referring to the type of data the function 
 works with.
 * "map" refers to the function's operation of applying a certain function 
 (in this case, `f`) to each element in the string.
 * The "i" at the end stands for index, indicating that the function `f` 
 takes an additional argument representing the index of each character 
 in the string.
  * The `ft_strmapi` function applies the function `f` to each character of the 
 * string `s`, passing it the index of the character and the character itself. 
 * The result of applying `f` to a character is stored in a new string, which 
 * the function returns.

 * 1. The function checks if the pointer `s` is equal to `NULL`. If so, it 
 * returns `NULL`.
 
 * 2. The function calculates the length of the string `s` using `ft_strlen`.

 * 3. The function allocates memory for a new string `result` of size `len + 1` 
 * (an extra character for the null character at the end of the string).

 * 4. If memory allocation fails, the function returns `NULL`.

 * 5. Then, the function goes through each character of the string `s`, applies 
 * the function `f` to it, and stores the result in the string `result`.

 * Note that the function `f` should be a function (any function)
 that takes the index of a 
 * character and the character itself, and returns a character.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(len * sizeof(char) + 1);
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

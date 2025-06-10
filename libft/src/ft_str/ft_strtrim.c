/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:59:19 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function: ft_strtrim (short for "string trim")
 * ---------------------------------------------
 * Trims leading and trailing characters from 's1' that are
 * present in 'set'.
 *
 * Function: ft_check_set
 * ----------------------
 * This helper function checks if a character 'c' is present
 * in the string 'set'. It iterates over 'set' and if 'c' is
 * found, it returns 1. If 'c' is not found in 'set', the
 * function returns 0.
 *
 * If 's1' or 'set' is NULL, the function ft_strtrim returns NULL.
 *
 * 'start' is initialized to 0 and then incremented until a
 * character in 's1' not in 'set' is found.
 * Функция `ft_check_set` принимает два аргумента: символ и строку.
 * В данном случае, `s1[start]` - это символ из строки `s1` на позиции `start`,
 * а `set` - это строка, в которой мы ищем этот символ.

* Таким образом, `ft_check_set(s1[start], set)` проверяет, содержится ли символ
* `s1[start]` в строке `set`. Если символ содержится, функция возвращает `1`,
* в противном случае - `0`.
 *
 * 'end' is initialized to the length of 's1' and then
 * decremented until a character in 's1' not in 'set' is
 * found, from the end of the string.
 *
 * Memory is allocated for the new string 'new_str' with a
 * size of 'end - start + 1'.
 *
 * If memory allocation fails (i.e., 'malloc' returns NULL),
 * the function returns NULL.
 *
 * Characters from 's1' starting at 'start' and of length
 * 'end - start + 1' are copied into 'new_str'.
 *
 * The function returns the new string 'new_str'.
 */
static int	ft_check_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && ft_check_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_check_set(s1[end - 1], set))
		end--;
	new_str = (char *)malloc((end - start + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1 + start, end - start + 1);
	return (new_str);
}

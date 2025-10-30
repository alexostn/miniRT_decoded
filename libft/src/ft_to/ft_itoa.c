/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:33:49 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * `itoa` stands for integer to ASCII. It's a function that converts an integer 
 * into a null-terminated string. The function uses the digits and their base 
 * (decimal, hexadecimal, etc.) to create the string representation of the input 
 * integer. The resulting string is stored in a buffer that should be large 
 * enough to hold the result.
 * 1. The function first calculates the length of the integer `n` (including the 
 * sign) using the helper function `ft_int_len(int n)`. This function counts the 
 * number of digits in `n` and adds 1 if `n` is less than or equal to 0.
 */

/* 
 * 2. It then allocates memory for the resulting string `result` with a size of 
 * `len + 1` to account for the null-terminating character.
 */

/* 
 * 3. If memory allocation fails, the function returns `NULL`.
 */

/* 
 * 4. It sets the last character of `result` to the null-terminating character 
 * (`'\0'`).
 */

/* 
 * 5. If `n` equals 0, the first character of `result` is set to '0'.
 */

/* 
 * 6. If `n` is less than 0, `n` is multiplied by -1 to convert it to a positive 
 * number, and the first character of `result` is set to '-'.
 */

/* 
 * 7. The function `ft_to_char(char *str, unsigned int nbr, long int len)` then 
 * converts `nbr` to a string, starting from the end of the string and moving 
 * towards the beginning, converting each digit of `nbr` to a character and 
 * storing it in the string.
 */

/* 
 * 8. Finally, the function returns `result`.
 */
static long int	ft_int_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*ft_to_char(char *str, unsigned int nbr, long int len)
{
	while (nbr > 0)
	{
		str[len--] = '0' + (nbr % 10);
		nbr = nbr / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char				*result;
	unsigned int		nbr;
	long int			len;

	len = ft_int_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len--] = '\0';
	if (n == 0)
		result[0] = '0';
	if (n < 0)
	{
		nbr = n * -1;
		result[0] = '-';
	}
	else
		nbr = n;
	result = ft_to_char(result, nbr, len);
	return (result);
}

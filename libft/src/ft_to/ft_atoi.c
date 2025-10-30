/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:09:18 by oostapen          #+#    #+#             */
/*   Updated: 2025/09/04 18:57:00 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function: ft_atoi (short for "ASCII to integer")
 * -----------------------------------------------
 * Converts the initial part of the string 'nptr' into an int.
 * Skips any leading whitespace, then interprets the following
 * characters as a number.
 * Returns the converted int value.
 * If a non-digit character is encountered, the conversion stops.
 * If a minus sign is encountered, the sign of the number is inverted.
 */
int	ft_atoi(const char *s)
{
	int			result;
	int			sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || *s == '\t' || *s == '\n'
		|| *s == '\r' || *s == '\f' || *s == '\v')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

// int main() {
//     char str1[] = "12345";      // Expected result: 12345
//     char str2[] = "   +987";     // Expected result: 987
//     char str3[] = "   -654";     // Expected result: -654
//     char str4[] = "  \t\n42abc"; // Expected result: 42
//     char str5[] = "words123";    // Expected result: 0
//     char str6[] = "";            // Expected result: 0

//     printf("Result of ft_atoi(\"%s\"): %d\n", str1, ft_atoi(str1));
//     printf("Result of ft_atoi(\"%s\"): %d\n", str2, ft_atoi(str2));
//     printf("Result of ft_atoi(\"%s\"): %d\n", str3, ft_atoi(str3));
//     printf("Result of ft_atoi(\"%s\"): %d\n", str4, ft_atoi(str4));
//     printf("Result of ft_atoi(\"%s\"): %d\n", str5, ft_atoi(str5));
//     printf("Result of ft_atoi(\"%s\"): %d\n", str6, ft_atoi(str6));

//     return 0;
// }

// int	main(void)
// {
// 	char	str[] = "  \t\n42abc";
// 	printf("Str4 again: %d\n", ft_atoi(str));
// 	return (0);
// }

// #include <stdlib.h>

// int main()
// {
// 	char str1[] = "--1234";
// 	char str2[] = "++5678";
// 	char str3[] = "sdf12345";
// 	printf("=== Testing ft_atoi ===\n");
// 	printf("atoi('%s') = %d\n", str1, ft_atoi(str1));
// 	printf("atoi('%s') = %d\n", str2, ft_atoi(str2));
// 	printf("atoi('%s') = %d\n", str3, ft_atoi(str3));
// 	printf("\n");
// 	printf("=== Testing ORIGINAL atoi ===\n");
// 	printf("atoi('%s') = %d\n", str1, atoi(str1));
// 	printf("atoi('%s') = %d\n", str2, atoi(str2));
// 	printf("atoi('%s') = %d\n", str3, atoi(str3));

// 	return (0);
// }

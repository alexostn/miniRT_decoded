
/*	PUT HEADER IN
 * ft_itoa_buf
 * -----------
 * Converts a non-negative integer n (expected range: 0–255) to a null-terminated string.
 * The result is written into the provided buffer `buf`, which must be at least 4 bytes.
 * No dynamic memory allocation is used.
 *
 * 1. If n is 100 or greater, writes three digits (hundreds, tens, units) and '\0'.
 * 2. If n is between 10 and 99, writes two digits (tens, units) and '\0'.
 * 3. If n is between 0 and 9, writes one digit and '\0'.
 *
 * Example:
 *   int n = 123;
 *   char buf[4];
 *   ft_itoa_buf(n, buf); // buf = "123"
 */

#include "../../inc/libft.h"

void	ft_itoa_buf(int n, char *buf)
{
	if (n < 0 || n > 999)
	{
		ft_strlcpy(buf, "ERR", 4);
		return;
	}
	if (n > 99)
	{
		buf[0] = (n / 100) + '0';
		buf[1] = ((n / 10) % 10) + '0';
		buf[2] = (n % 10) + '0';
		buf[3] = '\0';
	}
	else if (n > 9)
	{
		buf[0] = (n / 10) + '0';
		buf[1] = (n % 10) + '0';
		buf[2] = '\0';
	}
	else
	{
		buf[0] = n + '0';
		buf[1] = '\0';
	}
}

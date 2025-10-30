/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:05:26 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * The `ft_split` function splits the string `s` into an array of words,
 * using the character `c` as a delimiter. Here's a more detailed description:
 */

/* 
 * 1. If the input string `s` is `NULL`, the function returns `NULL`.
 */

/* 
 * 2. The function calls `ft_words_count` to count the number of words in `s`.
 * A word is a sequence of characters that are not the delimiter `c`.
 */

/* 
 * 3. The function allocates memory for the `token_v` array, which will hold
 * all the words. The size of the array is the number of words plus one.
 */

/* 
 * 4. If memory for the `token_v` array could not be allocated, the function
 * returns `NULL`.
 */

/* 
 * 5. The function sets the last element of the `token_v` array to `NULL`.
 */

/* 
 * 6. The function calls `ft_cpy_words` to copy words from `s` to `token_v`.
 * If `ft_cpy_words` returns `1` (indicating a memory allocation failure),
 * the function returns `NULL`.
 */

/* 
 * 7. If all words are successfully copied, the function returns `token_v`.
 */

/* 
 * The helper functions `ft_words_count`, `ft_save_malloc`, and `ft_cpy_words`
 * perform the following tasks:
 */

/* 
 * - `ft_words_count`: Counts the number of words in `s`, using `del`
 as a delimiter.
 */

/* 
 * - `ft_save_malloc`: Allocates memory for a word in the `token_v` array. If
 * memory allocation fails, it frees all previously allocated memory
 and returns `1`.
 * If memory is successfully allocated, it returns `0`.
 */

/* 
 * - `ft_cpy_words`: Copies words from `s` to `token_v`, using `del` as a
 delimiter.
 * It uses `ft_save_malloc` to allocate memory for each word. If `ft_save_malloc`
 * returns `1` (indicating a memory allocation failure),
 `ft_cpy_words` stops copying
 * words and returns `1`. If all words are successfully copied, it returns `0`.
 */
static int	ft_save_malloc(char **token_v, size_t word_index, size_t word_len)
{
	size_t	i;

	i = 0;
	token_v[word_index] = malloc(word_len);
	if (token_v[word_index] == NULL)
	{
		while (i < word_index)
			free(token_v[i++]);
		free(token_v);
		return (1);
	}
	return (0);
}

static int	ft_cpy_words(char **token_v, char const *s, char del)
{
	int		word_index;
	size_t	word_len;

	word_index = 0;
	while (*s)
	{
		word_len = 0;
		while (*s == del && *s)
			s++;
		while (*s != del && *s)
		{
			++word_len;
			s++;
		}
		if (word_len)
		{
			if (ft_save_malloc(token_v, word_index, word_len + 1))
				return (1);
			ft_strlcpy (token_v[word_index], s - word_len, word_len + 1);
		}
		++word_index;
	}
	return (0);
}

static size_t	ft_words_count(const char *s, char del)
{
	size_t	words_count;

	words_count = 0;
	while (*s != '\0')
	{
		while (*s == del)
			++s;
		if (*s != del && *s != '\0')
			words_count += 1;
		while (*s != del && *s != '\0')
			++s;
		if (*s == '\0')
			break ;
		++s;
	}
	return (words_count);
}

char	**ft_split(char const *s, char c)
{
	char	**token_v;
	size_t	words_count;

	if (s == NULL)
		return (NULL);
	words_count = ft_words_count(s, c);
	token_v = malloc((sizeof(char *) * (words_count +1)));
	if (token_v == NULL)
		return (NULL);
	token_v[words_count] = NULL;
	if (ft_cpy_words(token_v, s, c))
		return (NULL);
	return (token_v);
}

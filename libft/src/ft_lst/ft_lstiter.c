/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:18:19 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function:  ft_lstiter
 * --------------------
 * Iterates the list 'lst' and applies the function 'f'
 * to the content of each element.
 *
 *  lst: a pointer to the first element of the list
 *  f: a pointer to the function to be applied to the
 *     content of each element
 *
 *  This function first checks if `lst` or `f` is NULL.
 *  If so, it does nothing and simply returns.
 *
 *  If `lst` and `f` are not NULL, the function enters
 *  a `while` loop, which continues until the list
 *  becomes NULL (i.e., all elements of the list have
 *  been processed).
 *
 *  Inside the loop, the function calls the function 'f'
 *  on the 'content' of the current element, and then
 *  moves on to the next element by setting 'lst' equal
 *  to 'lst->next'.
 *
 *  Thus, the function goes through the entire list,
 *  applying the function 'f' to the content of each element.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

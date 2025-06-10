/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:13:19 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function:  ft_lstclear
 * --------------------
 * Deletes and frees the memory of the entire linked list.
 *
 *  lst: a pointer to the pointer to the first element
 *  del: a pointer to the function used to delete the
 *       content of each element
 *
 *  This function first checks if `lst` is NULL. If so,
 *  it does nothing and simply returns.
 *
 *  If `lst` is not NULL, the function enters a `while`
 *  loop, which continues until the list becomes NULL 
 *  (i.e., all elements of the list have been deleted).
 *
 *  Inside the loop, the function saves a pointer to the
 *  next element of the list in the `node` variable, 
 *  then deletes the current list element using the 
 *  `ft_lstdelone` function, and then moves on to the 
 *  next element by setting `*lst` equal to `node`.
 *
 *  Thus, the function goes through the entire list,
 *  deleting each element and freeing the memory it occupies.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		node = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = node;
	}
}

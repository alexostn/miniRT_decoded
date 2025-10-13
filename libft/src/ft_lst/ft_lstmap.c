/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:24:18 by oostapen          #+#    #+#             */
/*   Updated: 2025/10/14 00:49:31 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function:  ft_lstmap
 * --------------------
 * Creates a new list resulting from successive
 * applications of the function 'f' on the list 'lst'.
 *
 *  lst: a pointer to the first element of the list
 *  f: a pointer to the function to be applied to the
 *     content of each element
 *  del: a pointer to the function used to delete the
 *       content of an element in case of an error
 *
 *  This function first checks if `lst` or `f` is NULL.
 *  If so, it returns NULL. If `lst` and `f` are not NULL,
 *  the function enters a `while` loop, which continues
 *  until the list `lst` becomes NULL (i.e., all elements
 *  of the list have been processed). Inside the loop, the
 *  function creates a new list element `node` by applying
 *  the function 'f' to the 'content' of the current
 *  element. If the creation of the new element fails
 *  (i.e., `node` is NULL), the function clears the memory
 *  allocated for `node` using the `ft_lstclear` function
 *  and returns NULL. If the new element is successfully
 *  created, it is added to the end of the new list
 *  `new_list` using the `ft_lstadd_back` function, and
 *  then the function moves on to the next element by
 *  setting 'lst' equal to 'lst->next'. After processing
 *  all elements of the original list, the function
 *  returns the new list `new_list`.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;

	if (f == NULL || lst == NULL)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		node = ft_lstnew(f(lst->content));
		if (node == NULL)
		{
			ft_lstclear(&new_list, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}

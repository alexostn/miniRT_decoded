/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:57:56 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function:  ft_lstadd_back
 * --------------------
 * Adds a new element to the end of a linked list.
 *
 *  lst: a pointer to the pointer to the first element
 *  new: a pointer to the new element to be added
 *
 *  This function checks if `lst` or `new` is NULL. If so,
 *  it does nothing and simply returns.
 *
 *  If `lst` points to NULL (i.e., the list is empty),
 *  `new` becomes the first (and only) element.
 *
 *  If the list is not empty, the function enters a `while`
 *  loop, which continues until the `next` element of the
 *  current element becomes NULL. This means that the current
 *  element is the last in the list.
 *
 *  When the loop ends, `new` is added to the end of the list
 *  by setting the `next` of the last element to `new`.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_element;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current_element = *lst;
	while (current_element->next != NULL)
		current_element = current_element->next;
	current_element->next = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:49:12 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function:  ft_lstlast
 * --------------------
 * `ft_lstlast` retrieves the last element of a linked list. 
 * It takes a pointer to the first element of the list (`lst`).
 *
 * A pointer `current_element` is created inside the function, 
 * which initially points to the first element of the list. 
 * If this pointer is `NULL` (list is empty), the function returns `NULL`.
 *
 * If the list is not empty, the function enters a `while` loop, 
 * which continues until the `next` element 
 * of the current element becomes `NULL`. 
 * This means the current element is the last in the list.
 *
 * The function returns a pointer to the last element 
 * of the list when the loop ends.
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current_element;

	current_element = lst;
	if (current_element == NULL)
		return (NULL);
	while (current_element->next != NULL)
		current_element = current_element->next;
	return (current_element);
}

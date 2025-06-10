/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:23:35 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * The `ft_lstnew` function creates a new list element of type `t_list`.
 *
 * Here's how it works:
 *
 * 1. The function takes one argument: a pointer to `content` that will be 
 * stored in the new list element.
 *
 * 2. Then the function allocates memory for the new list element using the 
 * `malloc` function. The size of the memory allocated is equal to the size 
 * of the `t_list` structure.
 *
 * 3. If `malloc` returns `NULL` (which means that the memory was not 
 * successfully allocated), the function returns `NULL`.
 *
 * 4. If the memory was successfully allocated, the function sets the 
 * `content` field of the new list element to the passed `content` argument.
 *
 * 5. Then the function sets the `next` field of the new list element to 
 * `NULL`, indicating that this element is the last in the list.
 *
 * 6. Finally, the function returns a pointer to the new list element.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

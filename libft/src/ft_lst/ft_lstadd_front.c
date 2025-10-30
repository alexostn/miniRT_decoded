/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:03 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * The `ft_lstadd_front` function adds the element `new` at the beginning 
 * of the list `lst`.
 *
 * Here's how it works:
 *
 * 1. The function takes two arguments: a pointer to a pointer to the first 
 * element of the list `lst` and a pointer to the new element `new`.
 *
 * 2. If `lst` and `new` are not `NULL`, the function proceeds. Otherwise, 
 * it does nothing.
 *
 * 3. The function sets the `next` field of the new element `new` to the 
 * current first element of the list `lst`.
 *
 * 4. Then the function makes `new` the first element of the list `lst`, 
 * setting `*lst` to `new`.
 *
 * Thus, the new element is successfully added at the beginning of the list.
 * Here's how it works:
 * 1. `new` is a pointer to the new element that you want to add 
 * to the beginning of the list.
  `new->next` is the field in the `new` element 
 * that points to the next element in the list.
 *
 * 2. `lst` is a pointer to a pointer to the first element of the list. 
 `*lst` dereferences `lst`, giving you the first element of the list.
 *
 * 3. `new->next = *lst;` sets the `next` field of the `new` element to point
  to the current first element of the list. This effectively inserts the 
  `new` element
  at the beginning of the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

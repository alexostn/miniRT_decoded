/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:39:59 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/* 
 * The `ft_lstsize` function counts the number of elements in a linked 
 * list. Here's how it works:
 *
 * 1. The function takes one argument: a pointer to the first element of 
 * the list `lst`.
 *
 * 2. Then the function initializes a counter `count` to 0. This counter 
 * will be used to count the elements of the list.
 *
 * 3. The function enters a `while` loop that continues as long as `lst` 
 * is not `NULL`. In each iteration of the loop, the counter `count` is 
 * incremented by 1, and `lst` is updated to point to the next element of 
 * the list (`lst = lst->next`).
 *
 * 4. When `lst` becomes `NULL`, this means we have reached the end of the 
 * list, and the loop ends.
 *
 * 5. Finally, the function returns the value of the counter `count`, 
 * which represents the number of elements in the list.
 */
int	ft_lstsize(t_list *lst)
{
	int		count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/* 
 * In this line of code `lst = lst->next;`, we move to the next element 
 * of the linked list.
 *
 * `lst->next` accesses the `next` field of the current list element `lst`, 
 * which contains a pointer to the next element of the list.
 *
 * Then `lst = lst->next;` assigns this pointer to `lst`, thereby moving 
 * `lst` to the next element.
 *
 * This is typically used in a loop to traverse all elements of a linked list.
 */
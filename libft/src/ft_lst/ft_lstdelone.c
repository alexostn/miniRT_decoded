/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:05:45 by oostapen          #+#    #+#             */
/*   Updated: 2024/12/01 22:20:54 by oostapen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
 * Function:  ft_lstdelone
 * --------------------
 * Deletes a single element of a linked list.
 *
 *  lst: a pointer to the element to be deleted
 *  del: a pointer to the function used to delete
 *       the content of the element
 *
 *  This function first checks if `lst` is NULL. If so,
 *  it does nothing and simply returns.
 *
 *  If `lst` is not NULL, the function calls the `del`
 *  function on the `content` of the current element, 
 *  freeing the memory occupied by the content.
 *
 *  Then, the function frees the memory occupied by the
 *  list element itself using the `free` function.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
}

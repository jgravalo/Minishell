/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:08:50 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 09:56:51 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

t_quote	*quotenew(int start, int end)
{
	t_quote	*node;

	node = (t_quote *)malloc(sizeof (*node));
	check_malloc_error(node);
	node->start = start;
	node->end = end;
	node->next = NULL;
	return (node);
}

void	quoteback(t_quote **lst, t_quote *new)
{
	t_quote	*curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = quotelast(*lst);
	curr->next = new;
}

t_quote	*quotelast(t_quote *lst)
{
	if (!lst)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

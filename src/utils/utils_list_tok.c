/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_tok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:56:04 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 09:47:05 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

t_tok	*toknew(void *content)
{
	t_tok	*node;

	node = (t_tok *)malloc(sizeof (*node));
	check_malloc_error(node);
	node->tok = content;
	node->next = NULL;
	return (node);
}

int	tokback(t_tok **lst, t_tok *new)
{
	t_tok	*curr;

	if (!new | !lst)
		return (1);
	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	curr = toklast(*lst);
	curr->next = new;
	return (0);
}

t_tok	*toklast(t_tok *lst)
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

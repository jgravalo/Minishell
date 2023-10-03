/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:59:28 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/03 15:58:56 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

t_redir	*redirnew(int type)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->arg = NULL;
	node->type = type;
	node->next = NULL;
	return (node);
}

int	redirback(t_redir **lst, t_redir *new)
{
	t_redir	*curr;

	if (!new)
		return (1);
	if (!lst)
		return (2);
	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	curr = redirlast(*lst);
	curr->next = new;
	return (0);
}

t_redir	*redirlast(t_redir *lst)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:54:32 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 09:54:03 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

t_arg	*argnew(void *content)
{
	t_arg	*node;

	node = (t_arg *)malloc(sizeof (*node));
	check_malloc_error(node);
	node->arg = content;
	node->next = NULL;
	return (node);
}

int	argback(t_arg **lst, t_arg *new)
{
	t_arg	*curr;

	if (!new | !lst)
		return (1);
	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	curr = arglast(*lst);
	curr->next = new;
	return (0);
}

t_arg	*arglast(t_arg *lst)
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

int	argsize(t_arg *lst)
{
	int	c;

	c = 0;
	while (lst != NULL)
	{
		c++;
		lst = lst->next;
	}
	return (c);
}

void	argfront(t_arg **lst, t_arg *new)
{
	if (lst)
	{
		if (!lst || !new)
			return ;
		if (*lst == NULL)
		{
			*lst = new;
			new->next = NULL;
		}
		else
		{
			new->next = *lst;
			*lst = new;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:59:28 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 12:12:52 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*ft_redirlstnew(int type)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->path_arg = NULL;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	ft_redirlstadd_back(t_redir **lst, t_redir *new)
{
	t_redir	*curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = ft_redirlstlast(*lst);
	curr->next = new;
}

t_redir	*ft_redirlstlast(t_redir *lst)
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
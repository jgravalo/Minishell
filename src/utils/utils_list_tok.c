/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_tok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:56:04 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 12:20:11 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tok	*ft_toklstnew(void *content)
{
	t_tok	*node;

	node = (t_tok *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->tok = content;
	node->next = NULL;
	return (node);
}

void	ft_toklstadd_back(t_tok **lst, t_tok *new)
{
	t_tok	*curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = ft_toklstlast(*lst);
	curr->next = new;
}

t_tok	*ft_toklstlast(t_tok *lst)
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

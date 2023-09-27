/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:16:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/26 19:31:20 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

void	tokclear(t_tok **lst)
{
	t_tok	*curr;
	t_tok	*next;

	if (*lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->tok);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

void	argclear(t_arg **lst)
{
	t_arg	*curr;
	t_arg	*next;

	if (*lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->arg);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

void	redclear(t_redir **lst)
{
	t_redir	*curr;
	t_redir	*next;

	if (*lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		argclear(&(curr->arg));
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

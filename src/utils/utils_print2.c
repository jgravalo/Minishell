/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:53:20 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 12:13:08 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_printredirarglist(t_arg *arg)
{
	while (arg)
	{
		printf("redir path %s\n", arg->arg);
		arg = arg->next;
	}
}

void	ft_printarglist(t_arg *arg)
{
	while (arg)
	{
		printf("arg %s\n", arg->arg);
		arg = arg->next;
	}
}

void	ft_printdeflist(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_printarr(cmd[i]->args);
		if (cmd[i]->redir_x)
			ft_printredirlist(cmd[i]->redir_x);
		i++;
	}
}

void	ft_printlst(t_tok *lst)
{
	while (lst)
	{
		printf("%s\n", lst->tok);
		lst = lst->next;
	}
}

void	ft_printbothlst(t_tok *lst)
{
	while (lst)
	{
		printf("%s\n", lst->tok);
		printf("%s\n", lst->type);
		lst = lst->next;
	}
}

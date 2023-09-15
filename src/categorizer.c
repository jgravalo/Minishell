/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:38:00 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 12:30:47 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	categorizer(t_tok *tok)
{
	while (tok)
	{
		if (ft_strcmp(tok->tok, "|") == 0)
			tok->type = "PIPE";
		else if (ft_strcmp(tok->tok, ">") == 0
			|| ft_strcmp(tok->tok, "<") == 0
			|| ft_strcmp(tok->tok, ">>") == 0
			|| ft_strcmp(tok->tok, "<<") == 0)
			tok->type = "REDIR";
		else
			tok->type = "WORD";
		tok = tok->next;
	}
}

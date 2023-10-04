/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:38:00 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:49:00 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

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

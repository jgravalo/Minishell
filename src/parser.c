/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:40:11 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/26 18:33:01 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static int	count_pipes(t_shell *sh, t_tok *tok)
{
	int	count;

	count = 0;
	while (tok)
	{
		if (ft_strcmp(tok->type, "PIPE") == 0)
			count++;
		tok = tok->next;
	}
	sh->pipes = count;
	return (count);
}

static int	redir_type(t_tok *tok)
{
	if (ft_strcmp(tok->tok, "<") == 0)
		return (IN);
	if (ft_strcmp(tok->tok, ">") == 0)
		return (OUT);
	if (ft_strcmp(tok->tok, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(tok->tok, "<<") == 0)
		return (HERE);
	return (-1);
}

static void	init(t_cmd **cmd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		cmd[i] = malloc(sizeof (t_cmd));
		cmd[i]->red = NULL;
		cmd[i]->red_x = NULL;
		cmd[i]->arg = NULL;
		cmd[i]->arg_x = NULL;
		cmd[i]->args = NULL;
		i++;
	}
	cmd[i] = NULL;
}

static void	parse(t_tok *tok, t_cmd **cmd)
{
	int	j;
	int	redir;

	j = 0;
	redir = 0;
	while (tok)
	{
		if (ft_strcmp(tok->type, "WORD") == 0)
			argback(&(cmd[j]->arg), argnew(ft_strdup(tok->tok)));
		else if (ft_strcmp(tok->type, "REDIR") == 0)
		{
			redir = redir_type(tok);
			tok = tok->next;
			redirback(&(cmd[j]->red), redirnew(redir));
			argback(&(redirlast(cmd[j]->red)->arg), argnew(ft_strdup(tok->tok)));
		}
		else
			j++;
		tok = tok->next;
	}
	j++;
	cmd[j] = NULL;
}

void	parser(t_shell *sh)
{
	int	n;

	n = count_pipes(sh, sh->tok);
	sh->s_cmd = malloc(sizeof (t_cmd *) * (n + 2));
	init(sh->s_cmd, n + 1); 
	parse(sh->tok, sh->s_cmd);
}

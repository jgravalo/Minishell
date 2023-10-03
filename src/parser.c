/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:40:11 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/03 16:07:03 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static void	word(t_tok *tok, t_cmd **cmd, int j)
{
	char	*tmp;

	tmp = ft_strdup(tok->tok);
	if (!tmp)
		exit(1);
	if (argback(&(cmd[j]->arg), argnew(ft_strdup(tok->tok))))
		exit(1);
}

static void	redir_aux(t_tok *tok, t_cmd **cmd, int j)
{
	int	redir;

	redir = redir_type(tok);
	tok = tok->next;
	if (redirback(&(cmd[j]->red), redirnew(redir)))
		exit(1);
	if (argback(&(redirlast(cmd[j]->red)->arg),
			argnew(ft_strdup(tok->tok))))
		exit(1);
}

static void	parse(t_tok *tok, t_cmd **cmd)
{
	int	j;

	j = 0;
	while (tok)
	{
		if (ft_strcmp(tok->type, "WORD") == 0)
			word(tok, cmd, j);
		else if (ft_strcmp(tok->type, "REDIR") == 0)
			redir_aux(tok, cmd, j);
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

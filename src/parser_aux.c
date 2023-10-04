/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:51:56 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/10/04 10:42:39 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

int	count_pipes(t_shell *sh, t_tok *tok)
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

int	redir_type(t_tok *tok)
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

void	init(t_cmd **cmd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		cmd[i] = malloc(sizeof (t_cmd));
		check_malloc_error(cmd[i]);
		cmd[i]->red = NULL;
		cmd[i]->red_x = NULL;
		cmd[i]->arg = NULL;
		cmd[i]->arg_x = NULL;
		cmd[i]->args = NULL;
		cmd[i]->path = NULL;
		i++;
	}
	cmd[i] = NULL;
}

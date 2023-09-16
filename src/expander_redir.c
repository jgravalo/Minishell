/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:43:41 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 10:21:01 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static void	add_redir_node(t_shell *sh, t_cmd *cmd)
{
	char	*aux;

	if (sh->var_cat)
	{
		aux = ft_strjoin(arglast(cmd->red_x->arg)->arg, ft_strdup(sh->tmp));
		arglast(cmd->red_x->arg)->arg = ft_strdup(aux);
		free(aux);
	}
	else
	{
		if (!sh->next_redir)
		{
			redirback(&(cmd->red_x), redirnew(cmd->red->type));
			sh->next_redir = 1;
		}
		argback(&(redirlast(cmd->red_x)->arg), argnew(ft_strdup(sh->tmp)));
	}
}

static void	redir_loop(t_shell *sh, char *str, t_cmd *cmd)
{
	int	i;
	int	len;
	int	cpy;
	int	size;

	init_variables_loop(&i, &len, &cpy, &size);
	while (str[len])
	{
		advance_space(str, &len, &cpy);
		check_quoted(sh, &len);
		size = count_expand(sh, str, &len) + 1; 
		if (size > 1)
		{
			copy_and_remove_quotes(sh, size, str, &cpy);
			add_redir_node(sh, cmd);
		}
		free(sh->tmp);
	}
}

void	expand_redir(t_shell *sh, t_cmd **cmd)
{
	int		i;
	int		j;
	int		n;
	char	*expstr;

	init_variables(&i, &j, &n, sh);
	while (cmd[n])
	{
		while (cmd[n]->red)
		{
			while (cmd[n]->red->arg->arg[i])
			{
				expstr = ft_strdup(expand_str(sh, cmd[n]->red->arg, &i, &j));
				free(sh->tmp);
				if (expstr)
					redir_loop(sh, expstr, cmd[n]);
			}
			cmd[n]->red = cmd[n]->red->next;
			sh->next_redir = 0;
			i = 0;
			j = 0;
		}
		n++;
	}
}

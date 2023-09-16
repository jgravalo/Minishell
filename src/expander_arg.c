/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:41:49 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 10:20:30 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static void	add_arg_node(t_shell *sh, t_cmd *cmd)
{
	char	*aux;

	if (sh->var_cat)
	{
		aux = ft_strjoin(arglast(cmd->arg_x)->arg, ft_strdup(sh->tmp));
		arglast(cmd->arg_x)->arg = ft_strdup(aux);
		free(aux);
	}
	else
		argback(&(cmd->arg_x), argnew(ft_strdup(sh->tmp)));
}

static void	arg_loop(t_shell *sh, char *str, t_cmd *cmd)
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
			add_arg_node(sh, cmd);
			free(sh->tmp);
		}
	}
	sh->quote = NULL;
}

void	expand_args(t_shell *sh, t_cmd **cmd)
{
	int		i;
	int		j;
	int		n;
	char	*expstr;

	init_variables(&i, &j, &n, NULL);
	while (cmd[n])
	{
		cmd[n]->arg_x = NULL;
		while (cmd[n]->arg)
		{
			while (cmd[n]->arg->arg[i])
			{
				expstr = ft_strdup(expand_str(sh, cmd[n]->arg, &i, &j));
				free(sh->tmp);
				if (expstr)
					arg_loop(sh, expstr, cmd[n]);
			}
			cmd[n]->arg = cmd[n]->arg->next;
			i = 0;
			j = 0;
		}
		n++;
	}
}

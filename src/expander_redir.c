/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:43:41 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:49:37 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

static void	add_redir_node(t_shell *sh, t_cmd *cmd, t_redir *ptr)
{
	char	*aux;
	char	*tmp;

	if (sh->var_cat)
	{
		tmp = ft_strdup(sh->tmp);
		aux = ft_strjoin(arglast(cmd->red_x->arg)->arg, tmp);
		arglast(cmd->red_x->arg)->arg = ft_strdup(aux);
		free(aux);
		free(tmp);
	}
	else
	{
		if (!sh->next_redir)
		{
			redirback(&(cmd->red_x), redirnew(ptr->type));
			sh->next_redir = 1;
		}
		argback(&(redirlast(cmd->red_x)->arg), argnew(ft_strdup(sh->tmp)));
	}
}

static void	redir_loop(t_shell *sh, char *str, t_cmd *cmd, t_redir *ptr)
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
			add_redir_node(sh, cmd, ptr);
		}
		free(sh->tmp);
	}
}

static void	aux_expand_red(t_shell *sh, int *i, int *j)
{
	sh->next_redir = 0;
	*i = 0;
	*j = 0;
}

void	expand_redir(t_shell *sh, t_cmd **cmd)
{
	int		i;
	int		j;
	int		n;
	char	*expstr;
	t_redir	*ptr;

	init_variables(&i, &j, &n, sh);
	while (cmd[n])
	{
		ptr = cmd[n]->red;
		while (ptr)
		{
			while (ptr->arg->arg[i])
			{
				expstr = ft_strdup(expand_str(sh, ptr->arg, &i, &j));
				free(sh->tmp);
				if (expstr)
					redir_loop(sh, expstr, cmd[n], ptr);
				free(expstr);
			}
			ptr = ptr->next;
			aux_expand_red(sh, &i, &j);
		}
		n++;
	}
}

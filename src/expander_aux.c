/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:27:24 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 15:05:48 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_variables_loop(int *i, int *len, int *cpy, int *size)
{
	*i = 0;
	*len = 0;
	*cpy = 0;
	*size = 0;
}

void	init_variables(int *i, int *j, int *n, t_shell *sh)
{
	*i = 0;
	*j = 0;
	*n = 0;
	if (sh)
		sh->next_redir = 0;
}

void	advance_space(char *str, int *len, int *cpy)
{
	while (str[*len] == ' ')
	{
		(*len)++;
		(cpy)++;
	}
}

void	check_quoted(t_shell *sh, int *len)
{
	if (sh->quote && *len == sh->quote->start)
		sh->var_quoted = 1;
	else
		sh->var_quoted = 0;
}

void	copy_and_remove_quotes(t_shell *sh, int size, char *str, int *cpy)
{
	sh->tmp = (char *)malloc(sizeof (char) * size);
	copy_exp(sh->tmp, str, cpy, size);
	if (sh->var_quoted)
	{
		sh->tmp = remove_quotes(sh, sh->tmp);
		sh->quote = sh->quote->next;
	}
}

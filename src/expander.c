/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:01:54 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 13:28:44 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_quote(char *token, int *len, int *count, t_quote *quote)
{
	while (*len != quote->end)
	{
		(*count)++;
		(*len)++;
	}
	(*count)++;
	(*len)++;
	return (*count);
}

int	count_expand(t_shell *sh, char *token, int *len)
{
	int		count;
	int		i;
	t_quote	*ptr;

	i = 0;
	count = 0;
	ptr = sh->quote;
	sh->var_cat = 0;
	if (*len && token[*len] && token[*len - 1] && token[*len - 1] != ' ')
		sh->var_cat = 1;
	while (token[*len])
	{
		if (sh->var_quoted == 1 && *len == ptr->start)
			return (count_quote(token, len, &count, ptr));
		else if (sh->quote && sh->var_quoted == 0 && *len == sh->quote->start)
			return (count);
		else if (token[*len] == ' ')
		{
			(*len)++;
			return (count);
		}
		else
			move_ptrs(&count, len);
	}
	return (count);
}

void	copy_exp(char *dst, const char *src, int *cpy, size_t dstsize)
{
	int	i;
	int	quote;

	i = 0;
	while (src[*cpy] == ' ')
		(*cpy)++;
	while (i < (dstsize - 1))
	{
		dst[i] = src[*cpy];
		++i;
		(*cpy)++;
	}
	dst[i] = '\0';
}

void	expander(t_shell *sh, t_cmd **cmd)
{
	sh->quote = NULL;
	expand_args(sh, cmd);
	expand_redir(sh, cmd);
}

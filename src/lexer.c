/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:58 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 12:19:07 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	copy_token(char *dst, const char *src, int *cpy, size_t dstsize)
{
	int	i;
	int	quote;

	i = 0;
	while (i < (dstsize - 1))
	{
		dst[i] = src[*cpy];
		++i;
		(*cpy)++;
	}
	dst[i] = '\0';
}

static void	lexer_loop(char *line, t_shell *shell, int n)
{
	int	i;
	int	len;
	int	cpy;
	int	size;

	i = 0;
	len = 0;
	cpy = 0;
	size = 0;
	while (i < n)
	{
		while (line[len] == ' ')
		{
			len++;
			cpy++;
		}
		size = get_len(line, &len, &cpy) + 1;
		shell->tmp_tok = (char *)malloc(sizeof (char) * size);
		copy_token(shell->tmp_tok, line, &cpy, size);
		ft_toklstadd_back(&(shell->tok), ft_toklstnew(ft_strdup(shell->tmp_tok)));
		free(shell->tmp_tok);
		i++;
	}
}

void	lexer(t_shell *shell, char *line)
{
	int		n;

	shell->tok = NULL;
	n = count_tokens(line);
	lexer_loop(line, shell, n);
}

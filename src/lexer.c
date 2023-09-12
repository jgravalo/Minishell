/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:58 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/12 22:17:18 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	meta_len(char *line, int *len)
{	
	if (is_pipe(line[*len]) == 1)
	{	
		(*len)++;
		return (1);
	}
	else if (is_redir(&line[*len]) == 2)
	{	
		(*len) += 2;
		return (2);
	}
	else if (is_redir(&line[*len]) == 1)
	{	
		(*len)++;
		return (1);
	}
	return (0);
}

static int	get_len_quotes(char *line, int *len, int *cpy)
{
	int count;
	int quote;

	count = 0;
	quote = line[*len];
	count++;
	(*len)++;
	while (line[*len] != quote)
	{
		count++;
		(*len)++;
	}
	(*len)++;
	count++;
	return (count);
}

static int	get_len(char *line, int *len, int *cpy)
{
	int	count;

	count = 0;
	count = meta_len(line, len);
	if (count > 0)
		return (count);
	while (line[*len] != ' ' && is_meta(line[*len]) != 1 && line[*len] != '\0')
	{	
		if (line[*len] == '\'' || line[*len] == '\"')
			count += get_len_quotes(line, len, cpy);
		else
		{	
			count++;
			(*len)++;
		}
	}
	return (count);
}

static void	copy_token(char *dst, const char *src, int *cpy, size_t dstsize)
{
	int		i;
	int 	quote;

	i = 0;
	while (i < (dstsize - 1))
	{	
		dst[i] = src[*cpy];
		++i;
		(*cpy)++;
	}
	dst[i] = '\0';
}

void static	lexer_loop(char *line, t_shell *shell, int n)
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
		ft_lstadd_back(&(shell->tokens), ft_lstnew(ft_strdup(shell->tmp_tok)));
		free(shell->tmp_tok);
		i++;
	}
}

void lexer(t_shell *shell, char *line)
{
	int		n;

	shell->tokens = NULL;
	n = count_tokens(line);
	lexer_loop(line, shell, n);
	//ft_printarr(shell->tokens);
}

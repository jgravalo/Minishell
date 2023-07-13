/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:58 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/13 18:22:30 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	meta_len(char *line, int *len)
{
	if (is_pipe_or_dollar(line[*len]) == 1)
	{
		(*len)++;
		return (1);
	}
	else if (is_redir(line) == 2)
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

static int	get_len(char *line, int *len)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	count = meta_len(line, len);
	if (count > 0)
		return (count);
	else
	{
		while (line[*len] != ' ' && 
			is_meta(line[*len]) != 1 && line[*len] != '\0')
		{
			count++;
			(*len)++;
		}
		return (count);
	}
}

static void	copy_token(char *dst, const char *src, int *cpy, size_t dstsize)
{
	int	i;

	i = 0;
	while (i < (dstsize - 1))
	{
		dst[i] = src[*cpy];
		++i;
		(*cpy)++;
	}
	dst[i] = '\0';
}

void static	lexer_loop(char *line, char **tokens, int n)
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
		size = get_len(line, &len) + 1;
		tokens[i] = (char *)malloc(sizeof (char) * size);
		copy_token(tokens[i], line, &cpy, size);
		i++;
	}
	tokens[i] = NULL;
}

char	**lexer(char *line)
{
	int		n;
	char	**tokens;

	n = count_tokens(line);
	tokens = (char **)malloc(sizeof (char *) * (n + 1));
	lexer_loop(line, tokens, n);
	return (tokens);
}

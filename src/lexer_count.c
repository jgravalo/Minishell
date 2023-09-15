/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:39:35 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 12:22:19 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_meta(char *line, int *i, int *tokens)
{
	if (is_pipe(line[*i]) == 1)
	{
		(*tokens)++;
		(*i)++;
		return (1);
	}
	else if (is_redir(&line[*i]) == 2)
	{
		(*tokens)++;
		(*i) += 2;
		return (1);
	}
	else if (is_redir(&line[*i]) == 1)
	{
		(*tokens)++;
		(*i)++;
		return (1);
	}
	return (0);
}

static void	quotes(char *line, int *i, int *tokens, int *word)
{
	char	quote;

	quote = line[*i];
	if (*word == 0)
	{
		(*tokens)++;
		*word = 1;
	}
	(*i)++;
	while (line[*i] != quote)
		(*i)++;
	(*i)++;
}

static void	loop(char *line, int *i, int *tokens, int *word)
{
	if (line[*i] == '\'' || line[*i] == '\"')
		quotes(line, i, tokens, word);
	else if (count_meta(line, i, tokens) > 0)
		*word = 0;
	else if (line[*i] != ' ' && *word == 0)
	{
		(*i)++;
		(*tokens)++;
		*word = 1;
	}
	else if (line[*i] == ' ' && *word == 1)
	{
		(*i)++;
		*word = 0;
	}
	else
		(*i)++;
}

int	count_tokens(char *line)
{
	int	i;
	int	tokens;
	int	word;

	i = 0;
	tokens = 0;
	word = 0;
	while (line[i])
		loop(line, &i, &tokens, &word);
	return (tokens);
}

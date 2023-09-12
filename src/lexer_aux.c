/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:39:35 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/12 20:00:51 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_redir(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	else if (str[i] == '<' || str[i] == '>')
		return (1);
	else
		return (0);
}

static int	count_meta(char *line, int *i, int *tokens, int word)
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

static void	loop(char *line, int *i, int *tokens, int *word)
{	
	char quote;

	if (line[*i] == '\'' || line[*i] == '\"')
	{	
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
	else if (count_meta(line, i, tokens, *word) > 0)
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

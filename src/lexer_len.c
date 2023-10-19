/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:32:52 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/19 19:56:40 by dtome-pe         ###   ########.fr       */
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

static int	get_len_quotes(char *line, int *len)
{
	int	count;
	int	quote;

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

int	get_len(char *line, int *len)
{
	int	count;

	count = 0;
	count = meta_len(line, len);
	if (count > 0)
		return (count);
	while (!is_space(line[*len]) && is_meta(line[*len]) != 1
		&& line[*len] != '\0')
	{
		if (line[*len] == '\'' || line[*len] == '\"')
			count += get_len_quotes(line, len);
		else
		{
			count++;
			(*len)++;
		}
	}
	return (count);
}

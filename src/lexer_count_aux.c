/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:31:06 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/19 19:48:18 by dtome-pe         ###   ########.fr       */
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

int	is_meta(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

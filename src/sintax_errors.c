/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:23:10 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/18 15:07:37 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/minishell.h"
#include "../inc/utils.h"
/**/

int pipe_error()
{
	write(2, "bash: syntax error near unexpected token `|'\n", 46);
	return (258);
}

int	search_pipe(t_shell *shell)
{
	char	*line;
	char	*tmp;
	char	*tmp2;

//	printf("readline before = <%s>\n", shell->readline);
	line = "";
	while (ft_strcmp(line, "") == 0)
		line = readline("> ");
	tmp = ft_strjoin(" ", line);
	tmp2 = ft_strjoin(shell->readline, tmp);
	free(line);
	free(shell->readline);
	shell->readline = tmp2;
	free(tmp);
//	printf("readline after = <%s>\n", shell->readline);
	if (parse_pipes(shell) != 0)
		return (258);
	return (0);
}


int		loop_pipes(t_shell *shell, int *pipe)
{
	int		i;
	char	quote;

	i = 0;
	while (shell->readline[i])
	{
		if (shell->readline[i] && shell->readline[i] != ' '
			&& shell->readline[i] != '|')
			*pipe = 0;
		if (shell->readline[i] == '\'' || shell->readline[i] == '\"')
		{
			quote = shell->readline[i];
			i++;
			while (shell->readline[i] != quote)
				i++;
		}
		if (shell->readline[i] == '|')
		{
			if (*pipe == 1)
				return (pipe_error());
			*pipe = 1;
		}
		i++;
	}
	return (0);
}
int		parse_pipes(t_shell *shell)
{
	int		pipe;

	if (!ft_strchr(shell->readline, '|'))
		return (0);
	pipe = 1;
	
	if (loop_pipes(shell, &pipe) != 0)
		return (258);
	if (pipe == 1)
		if (search_pipe(shell) != 0)
			return (258);
	return (0);
}

int quote_error(char quote)
{
	write(2, "bash: syntax error near expected token `", 41);
	write(2, &quote, 1);
	write(2, "\'\n", 2);
	return (258);
}

int	parse_quotes(t_shell *shell)
{
	int		i;
	char	quote;

	i = 0;
	if (!ft_strchr(shell->readline, '\'') && !ft_strchr(shell->readline, '\"'))
		return (0);
	while (shell->readline[i])
	{
		if (shell->readline[i] == '\'' || shell->readline[i] == '\"')
		{
			quote = shell->readline[i];
			i++;
			while (shell->readline[i] && shell->readline[i] != quote)
				i++;
			if (!shell->readline[i])
				return (quote_error(quote));
		}
		i++;
	}
	return (0);
}

//int	parse_redirs()

int sintax_errors(t_shell *sh)
{
	if (parse_quotes(sh) != 0 || parse_pipes(sh) != 0)
	{
		sh->exit = 258;
		add_history(sh->readline);
		return (258);
	}
	return (0);
}

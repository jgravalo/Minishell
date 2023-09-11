/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:23:10 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/08 17:16:48 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/minishell.h"
/**/
static char *search_pipe(t_shell *shell)
{
	char	*line;
	char	*tmp;
	char	*tmp2;
	int		pipe;
//	char	c = 

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

int		*parse_pipes(t_shell *shell)
{
	int		i;
	int		pipe;
	char	quote;

	if (!ft_strchr(shell->readline, '|'))
		return (0);
	i = 0;
	pipe = 1;
//	printf("readline = <%s>\n", shell->readline);
	while (shell->readline[i])
	{
		if (shell->readline[i] && shell->readline[i] != ' '
				&& shell->readline[i] != '|')
			pipe = 0;
		if (shell->readline[i] == '\'' || shell->readline[i] == '\"')
		{
			quote = shell->readline[i];
			i++;
			while (shell->readline[i] != quote)
				i++;
		}
		if (shell->readline[i] == '|')
		{
			if (pipe == 1)
			{
				write(2, "bash: syntax error near unexpected token `|'\n", 50);
				return (258);
			}
			else
				pipe = 1;
			// aparte si el pipe final queda vacio, hay que buscar un nuevo comando con otra readline
		}
		i++;
	}
	if (pipe == 1)
		if (search_pipe(shell) != 0)
		{
			shell->exit = 258;
			return (258);
		}
	return (0);
}

/*
int		*parse_pipes(t_shell *shell)
{
	printf("readline = <%s>\n", shell->readline);
	return (0);
}*/

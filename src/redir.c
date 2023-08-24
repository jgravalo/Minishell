/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:27:26 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/24 13:00:50 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	len_redir(char *line)
{
	int	i;
	char quote;

	i = 0;
	if ((*line == '>' || *line == '<') && ++i)
		line++;
	if ((*line == '>' || *line == '<') && ++i)
		line++;
	while (*line && *line == ' ' && ++i)
		line++;
	if ((*line == '\"' || *line == '\'') && ++i)
	{	
		quote = *line;
		line++;
		while(*line != quote && ++i)
			line++;
	}
	while (*line && *line != ' ' && ++i)
		line++;

	return (i);
}

static char* no_redir(char **m, char *line)
{	
	char quote;
	int i;
	
	i = 0;
	while (*line && *line != '<' && *line != '>' && ++i)
	{
		if (*line == '\'' || *line == '\"')
		{
			quote = *line;
			line++;
			while (*line != quote)
				line++;
			line++;
		}
		line++;
	}
	return (ft_substr(line - i, 0, i));
}

char	**ft_split_redir(char *line)
{
	char	**m;
	int		j;
	int		len;

	m = (char **)malloc(sizeof(char *) * (count_redir(line) + 1));
	j = -1;
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			len = len_redir(line);
			m[++j] = ft_substr(line, 0, len);
			line += len;
		}
		else
			m[++j] = no_redir(m, line);
	}
	m[++j] = NULL;
	return (m);
}

void	make_redir(t_shell *shell)
{	
	char *str;
	int		start_line;

	str = NULL;
	if (make_stdin_stdout(shell)) // si devuelve 1 era redir in (0) o out (1)
		return ;
	start_line = shell->line_number; // sino es heredoc
	while (ft_strcmp(str, shell->delimiter))
	{	
		str = readline("> ");
		if (str == NULL)
		{
			write_heredoc_eof(shell, start_line);
			break;
		}
			shell->line_number++;
	}
}

char *parse_redir(char *line, t_shell *shell)
{
	char **args;
	char *cmd;
	int i;
	int j;

	if (is_there_redir(line) == 0) // si no hay redir a procesar, fuera
		return (line);
	cmd = ft_strdup("");
	args = ft_split_redir(line);
	i = 0;
	while (args[i])
	{	
		j = 0;
		if (args[i][0] == '<' || args[i][0] == '>')
			prepare_redir(args[i], shell);
		else
		{	
			while (args[i][j] == ' ')
				j++;
			cmd = ft_strjoin(cmd, &args[i][j]);
		}
		i++;
	}
	return (cmd);
}

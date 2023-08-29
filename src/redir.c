/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:27:26 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/29 11:57:19 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char* no_redir(char **m, char *line, int *i)
{	
	char quote;
	
	*i = 0;
	while (*line && *line != '<' && *line != '>' && ++(*i))
	{
		if (*line == '\'' || *line == '\"')
		{
			quote = *line;
			line++;
			while (*line != quote)
			{
				(*i)++;
				line++;
			}	
			line++;
			(*i)++;
		}
		else
			line++;
	}
	return (ft_substr(line - *i, 0, *i));
}

char	**ft_split_redir(char *line)
{
	char	**m;
	int		j;
	int		len;
	int 	i;

	i = 0;
	m = (char **)malloc(sizeof(char *) * (count_redir(line) + 1));
	j = -1;
	while (*line)
	{	
		if (*line == ' ')
			line++;
		else if (*line == '<' || *line == '>')
		{
			len = len_redir(line);
			m[++j] = ft_substr(line, 0, len);
			line += len;
		}
		else
		{	
			m[++j] = no_redir(m, line, &i);
			line += i;
		}
	}
	m[++j] = NULL;
	return (m);
}

int make_stdin_stdout(t_shell *shell)
{	
	if (shell->redir_type == 0)
	{	
		dup2(shell->infd, shell->redir_type);
		close(shell->infd);
		return (1);
	}
	else if (shell->redir_type == 1)
	{	
		dup2(shell->outfd, shell->redir_type);
		close(shell->outfd);
		return (1);
	}
	return (0);
}

static void make_heredoc(t_shell *shell)
{	
	int start_line;
	char *str;
	char *heredoc;
	int delimiter;

	delimiter = 0;
	str = NULL;
	heredoc = ft_strdup("");
	start_line = shell->line_number;
	while (1)
	{	
		str = readline("> ");
		if (ft_strcmp(str, shell->delimiter) == 0)
			break;
		else if (str == NULL)
		{
			write_heredoc_eof(shell, start_line);
			break;
		}
		str = ft_strjoin(str, "\n");
		heredoc = ft_strjoin(heredoc, str);
		shell->line_number++;
		//free (str);
	}
	write(shell->infd, heredoc, ft_strlen(heredoc));
	close(shell->infd);
	shell->infd = open(shell->here_tmp, O_RDONLY);
	dup2(shell->infd, STDIN_FILENO);
	close(shell->infd);
	unlink(shell->here_tmp);
}

void	make_redir(t_shell *shell)
{	
	if (make_stdin_stdout(shell)) // si devuelve 1 era redir in (0) o out (1)
		return ;
	else
		make_heredoc(shell);
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
/* 	printf("redir args son:\n");
	ft_printarr(args); */
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

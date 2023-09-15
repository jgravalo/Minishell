/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:27:26 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 13:10:39 by theonewhokn      ###   ########.fr       */
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

static	void handle_signal(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	make_redir(t_shell *shell, int n)
{	
	if (shell->struct_cmd[n]->infile > -1)
	{	
		dup2(shell->struct_cmd[n]->infile, STDIN_FILENO);
		close(shell->struct_cmd[n]->infile);
	}
	if (shell->struct_cmd[n]->outfile > -1)
	{	
		dup2(shell->struct_cmd[n]->outfile, STDOUT_FILENO);
		close(shell->struct_cmd[n]->outfile);
	}
}

/* char *parse_redir(char *line, t_shell *shell, int n)
{
	char **args;
	char *cmd;
	int i;
	int j;
	int redir_num;

	redir_num = 0;
	if (is_there_redir(line) == 0) // si no hay redir a procesar, fuera
		return (line);
	cmd = NULL;
	args = ft_split_redir(line);
	shell->struct_cmd[n]->redir = (t_redir **)malloc(sizeof (t_redir *) * (count_redir_arr(args) + 1));
	shell->struct_cmd[n]->redir[count_redir_arr(args)] = NULL;
	printf("redir args son:\n");
	ft_printarr(args);
	i = 0;
	while (args[i])
	{	
		j = 0;
		if (args[i][0] == '<' || args[i][0] == '>')
		{
			if (prepare_redir(args[i], shell, n, redir_num) != 0)
				return (NULL);
			free(args[i]);
			redir_num++;
			if (g_exit == 1)
			{
				shell->exit = 130;
				return (NULL);
			}
		}
		else
		{	
			while (args[i][j] == ' ')
				j++;
			cmd = ft_strjoin(cmd, &args[i][j]);
		}
		i++;
	}
	free(line);
	free(args);
	return (cmd);
} */

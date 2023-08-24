/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:27:26 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/24 11:15:17 by theonewhokn      ###   ########.fr       */
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
//	while (*line && *line == ' ' && ++i)
//		line++;
	return (i);
}

int	count_redir(char *line)
{
	int	i;

	i = 0;
	while (*line != '\0')
	{
		if ((*line == '<' || *line == '>') && ++i)
			line += len_redir(line);
		if (*line && *line != '<' && *line != '>' && ++i)
			while (*line && *line != '<' && *line != '>')
			{
				//parse_quotes
				/*
				if (*line == '\'' && ++line && ++i)
					while (*line && *line != '\'' && ++i)
						line++;
				*/
				line++;
			}
	}
	return (i);
}

char	**ft_split_redir(char *line)
{
	char	**m;
	int		i;
	int		j;
	int		len;
	char	quote;

//	printf("count = %d\n", count_redir(line));
//	printf("aqui\n");
	m = (char **)malloc(sizeof(char *) * (count_redir(line) + 1));
	j = -1;
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			len = len_redir(line);
			m[++j] = ft_substr(line, 0, len);
			line += len;
//			printf("m[%d] = |%s|\n", j, m[j]);
		}
		else
		{
			i = 0;
			while (*line && *line != '<' && *line != '>' && ++i)
			{
				//parse_quotes
				if (*line == '\'' || *line == '\"')
				{
					quote = *line;
					line++;
					while (*line != quote)
						line++;
					line++;
				}
				/*
				if (*line == '\'' && ++line && ++i)
					while (*line && *line != '\'' && ++i)
						line++;
				*/
				line++;
			}
			m[++j] = ft_substr(line - i, 0, i);
			//m[j] = free_quotes(m[j]);
//			printf("m[%d] = |%s|\n", j, m[j]);
		}
	}
	m[++j] = NULL;
	return (m);
}

char	*get_redir(char *line)
{
	while (*line == '>' || *line == '<')
		line++;
	while (*line == ' ')
		line++;
	return (line);
}

static char* remove_quotes(char *str)
{
	int i;
	int j;
	char *new_str;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\"')
			i++;
		else
		{
			i++;
			j++;
		}
	}
	new_str = (char *)malloc(sizeof (char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i])
	{	
		if (str[i] == '\"' || str[i] == '\"')
			i++;
		else
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
	}
	return (new_str);
}

static void	prepare_redir(char *line, t_shell *shell)
{
	char *tmp;
	int fd;
	int type;

//	printf("line is |%s|\n", line);
	tmp = get_redir(line);
//	printf("redir = |%s|\n", tmp);
	if (line[0] == '<' && line[1] != '<')
	{	/*
		if (access(tmp, F_OK) != 0)
		{
			printf("%s: %s\n", tmp, strerror(2));
			exit(1);
		}
		if (access(tmp, R_OK) != 0 || access(tmp, W_OK) != 0
			|| access(tmp, X_OK) != 0)
		{
			printf("%s: %s\n", tmp, strerror(13));
			exit(1);
		}
		*/
		fd = open(tmp, O_RDONLY);
//		printf("%s\n", strerror(errno));
		shell->infd = fd;
		shell->saved_stdin = dup(0);
		shell->redir_type = 0;
	}
	else if (line[0] == '<' && line[1] == '<')
	{
		/*heredoc*/
		shell->delimiter = tmp;
		if(ft_strchr(tmp, '\"') || ft_strchr(tmp, '\''))
		{
			shell->heredoc_quoted = 1;
			shell->delimiter = remove_quotes(shell->delimiter);
		}
		shell->saved_stdin = dup(0);
		shell->redir_type = 2;
	}
	else if (line[0] == '>' && line[1] != '>')
	{	/*
		if (access(tmp, F_OK) == 0 && access(tmp, W_OK) != 0)
		{
			printf("%s: %s\n", tmp, strerror(13));
			exit(1);
		}
		*/
//		ft_printarr(tmp);
		fd = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 00644);
		shell->outfd = fd;
		shell->saved_stdout = dup(1);
		shell->redir_type = 1;
//	printf("aqui\n");
	}
	else if (line[0] == '>' && line[1] == '>')
	{	/*
		if (access(tmp, F_OK) == 0 && access(tmp, W_OK) != 0)
		{
			printf("%s: %s\n", tmp, strerror(13));
			exit(1);
		}
		*/
		fd = open(tmp, O_RDWR | O_CREAT | O_APPEND, 00644);
		shell->outfd = fd;
		shell->saved_stdout = dup(1);
		shell->redir_type = 1;
	}
//	free_m(tmp);
}

void	make_redir(t_shell *shell)
{	
	char *str;
	int		start_line;

	str = NULL;
	if (shell->redir_type == 0)
	{	
		dup2(shell->infd, shell->redir_type);
		close(shell->infd);
	}
	else if (shell->redir_type == 1)
	{	
		dup2(shell->outfd, shell->redir_type);
		close(shell->outfd);
	}
	else 
	{	
		start_line = shell->line_number;
		while (ft_strcmp(str, shell->delimiter))
		{	

			str = readline("> ");
			if (str == NULL)
			{
				write(2, "bash: warning: here-document at line ", 37);
				write(2, ft_itoa(start_line), ft_strlen(ft_itoa(shell->line_number)));
				write(2, " delimited by end-of-file (wanted `", 35);
				write(2, shell->delimiter, ft_strlen(shell->delimiter));
				write(2, "')\n", 3);
				break;
			}
				shell->line_number++;
		}
	}
}

int recover_std(t_shell *shell)
{
	if (shell->redir_type == 0)
		dup2(shell->saved_stdin, 0);
	if (shell->redir_type == 1)
		dup2(shell->saved_stdout, 1);
	return (shell->exit);
}

static int 	is_there_redir(char *line)
{	
	char quote;

	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			quote = *line;
			line++;
			while (*line != quote)
				line++;
			line++;
		}
		else if (*line == '<' || *line == '>')
			return (1);
		else	
			line++;
	}
	return (0);
}

char *parse_redir(char *line, t_shell *shell)
{
	char **args;
	char *cmd;
	char *c;
	int i;
	int j;

	if (is_there_redir(line) == 0) // si no hay redir a procesar, fuera
		return (line);
	cmd = ft_strdup("");
	args = ft_split_redir(line);
	//printf("split redir is:\n");
	ft_printarr(args);
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
/* 	printf("redir es %d\n", shell->redir_type);
	if (shell->delimiter != NULL)
		printf("delimiter is %s\n", shell->delimiter);
	printf("frase al salir de parseredir es %s\n", cmd); */
//	printf("aqui\n");
	//free_m(args);
	return (cmd);
}
/*
int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	//
	printf("len = %d\n", len_redir(argv[1]));
	printf("count = %d\n", count_redir(argv[1]));
	char **m = ft_split_redir(argv[1]);
	int i;
	for (i = 0; m[i]; i++)
		printf("m[%d] = |%s|\n", i, m[i]);
	//
	char *cmd = parse_redir(argv[1]);
	printf("cmd = |%s|\n", cmd);
	return (0);
}*/

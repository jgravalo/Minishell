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
				line++;
			}
	}
	return (i);
}

void write_heredoc_eof(t_shell *shell, int start_line)
{
	write(2, "bash: warning: here-document at line ", 37);
	write(2, ft_itoa(start_line), ft_strlen(ft_itoa(shell->line_number)));
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, shell->delimiter, ft_strlen(shell->delimiter));
	write(2, "')\n", 3);
}

int recover_std(t_shell *shell)
{
	if (shell->redir_type == 0)
		dup2(shell->saved_stdin, 0);
	if (shell->redir_type == 1)
		dup2(shell->saved_stdout, 1);
	return (shell->exit);
}

int 	is_there_redir(char *line)
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
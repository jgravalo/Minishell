#include "../inc/minishell.h"

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
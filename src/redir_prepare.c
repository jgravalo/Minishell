#include "../inc/minishell.h"

static int prepare_infile(t_shell *shell, char *tmp)
{	
	shell->infd = open(tmp, O_RDONLY);
	if (shell->infd == -1)
	{
		shell->exit = 1;
		cmd_error(tmp, errno, 1);
		if (shell->pipex == 0)
			return (-1);
		else
			exit(shell->exit);
	}
	shell->saved_stdin = dup(0);
	shell->redir_type = 0;
	return (0);
}

static void prepare_heredoc(t_shell *shell, char *tmp)
{	
	shell->delimiter = ft_strdup(tmp);
	shell->infd = open(shell->here_tmp, O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
	if(ft_strchr(tmp, '\"') || ft_strchr(tmp, '\''))
	{
		shell->heredoc_quoted = 1;
		shell->delimiter = remove_quotes(shell->delimiter);
	}
	shell->saved_stdin = dup(0);
	shell->redir_type = 2;
}

static int prepare_outfile(t_shell *shell, char *tmp, int append)
{	
	if (append == 0)
		shell->outfd = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 00644);
	else
		shell->outfd = open(tmp, O_RDWR | O_CREAT | O_APPEND, 00644);
	if (shell->outfd == -1)
	{
		cmd_error(tmp, errno, 1);
		shell->exit = 1;
		if (shell->pipex == 0)
			return (-1);
		else
			exit(shell->exit);
	}
	shell->saved_stdout = dup(1);
	shell->redir_type = 1;	
	return (0);
}

void	prepare_redir(char *line, t_shell *shell)
{	
	//printf("entra en prepare redir\n");
	char *tmp;

//	printf("line = <%s>\n", line);
	tmp = get_redir(line);
//	printf("tmp = <%s>\n", tmp);
	if (line[0] == '<' && line[1] != '<')
	{
		if (prepare_infile(shell, tmp) == -1)
			return ;
	}
	else if (line[0] == '<' && line[1] == '<')
	{	
		prepare_heredoc(shell, tmp);
		return ;
	}
	else if (line[0] == '>' && line[1] != '>')
	{	
		if (prepare_outfile(shell, tmp, 0) == -1)
			return ;
	}
	else if (line[0] == '>' && line[1] == '>')
	{	
		if (prepare_outfile(shell, tmp, 1) == -1)
			return ;
	}
}

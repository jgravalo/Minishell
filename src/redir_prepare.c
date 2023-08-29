#include "../inc/minishell.h"

static int prepare_infile(t_shell *shell, char *tmp)
{	
	int fd;

	if (access(tmp, F_OK) != 0)
	{	
		shell->exit = 1;
		cmd_error(tmp, errno, 1);
		if (shell->pipex == 0)
			return (-1);
		else
			exit(shell->exit);
	}
	else if (access(tmp, R_OK) != 0)
	{	
		shell->exit = 1;
		cmd_error(tmp, errno, 1);
		if (shell->pipex == 0)
			return (-1);
		else
			exit(shell->exit);
	}
	fd = open(tmp, O_RDONLY);
	shell->infd = fd;
	shell->saved_stdin = dup(0);
	shell->redir_type = 0;
	return (0);
}

static void prepare_heredoc(t_shell *shell, char *tmp)
{	
	shell->delimiter = tmp;
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
	int fd;

	if (access(tmp, F_OK) == 0 && access(tmp, W_OK) != 0)
	{	
		cmd_error(tmp, 13, 1);
		shell->exit = 1;
		if (shell->pipex == 0)
			return (-1);
		else
			exit(shell->exit);
	}
	if (append == 0)
		fd = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 00644);
	else
		fd = open(tmp, O_RDWR | O_CREAT | O_APPEND, 00644);
	shell->outfd = fd;
	shell->saved_stdout = dup(1);
	shell->redir_type = 1;	
	return (0);
}

void	prepare_redir(char *line, t_shell *shell)
{	
	//printf("entra en prepare redir\n");
	char *tmp;
	int type;

	tmp = get_redir(line);
	if (line[0] == '<' && line[1] != '<')
	{
		if (prepare_infile(shell, tmp) == -1)
			return ;
	}
	else if (line[0] == '<' && line[1] == '<')
	{	
		printf("entra en en prepare heredoc\n");
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
 #include "../inc/minishell.h"

static	void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 1;
		write(1, "\n", 1);
	}
	if (sig == SIGQUIT)
		return  ;
}

static void prepare_infile(t_shell *shell, char *tmp, int n, int redir_num)
{	
	shell->struct_cmd[n]->redir[redir_num]->path = ft_strdup(tmp);
	shell->struct_cmd[n]->redir[redir_num]->type = 0;
	free(tmp);
}

static void prepare_heredocs(t_shell *shell, char *tmp, int n, int redir_num)
{	
	pid_t	pid;
	int		status;

	shell->heredoc_quoted = 0;
	shell->delimiter = ft_strdup(tmp);
	shell->struct_cmd[n]->redir[redir_num]->heredoc_fd = open(shell->here_tmp, O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
	shell->struct_cmd[n]->redir[redir_num]->type = 1;
	if(ft_strchr(tmp, '\"') || ft_strchr(tmp, '\''))
	{
		shell->heredoc_quoted = 1;
		shell->delimiter = remove_quotes(shell, shell->delimiter);
	}
	shell->saved_stdin = dup(0);
	shell->redir_type = 2;
	pid = fork();
	if (pid > 0)
	{	
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		waitpid(pid, &status, 0);
	}
/* 	else if (pid == 0)
		make_heredoc(shell, n, redir_num); */
}

static void prepare_outfile(t_shell *shell, char *tmp, int n, int redir_num)
{	
	tmp = remove_quotes(shell, tmp);
	shell->struct_cmd[n]->redir[redir_num]->path = ft_strdup(tmp);
	shell->struct_cmd[n]->redir[redir_num]->type = 2;
	free(tmp);
}

static void prepare_append(t_shell *shell, char *tmp, int n, int redir_num)
{	
	tmp = remove_quotes(shell, tmp);
	shell->struct_cmd[n]->redir[redir_num]->path = ft_strdup(tmp);
	shell->struct_cmd[n]->redir[redir_num]->type = 3;
	free(tmp);
}

int	check_redir_errors(char	*redir)
{
	if (access(redir, F_OK) != 0)
	{
		write(2, ": No such file or directory\n", 29);
		return (1);
	}
	if (access(redir, R_OK) != 0
		|| access(redir, W_OK) != 0
		|| access(redir, X_OK) != 0)
	{
		write(2, ": Permission denied\n", 21);
		return (1);
	}
	return (0);
}

int		prepare_redir(char *line, t_shell *shell, int n, int redir_num)
{	
	char *tmp;

	tmp = get_redir(line);

	 //no esta finalizado. hay que obtener el fallo correspondiente para el tipo de error
	if (check_redir_errors(tmp) != 0)
	{
		shell->exit = 1;
		g_exit = 2;// para no interferir en el funcionamiento de g_exit == 1
		return (1);
	}

	shell->struct_cmd[n]->redir[redir_num] = malloc(sizeof (t_redir));
	if (line[0] == '<' && line[1] != '<' && shell->redir_error[n] != 1)
		prepare_infile(shell, ft_strdup(tmp), n, redir_num);
	else if (line[0] == '<' && line[1] == '<')
		prepare_heredocs(shell, tmp, n, redir_num);
	else if (line[0] == '>' && line[1] != '>' && shell->redir_error[n] != 1)
		prepare_outfile(shell, ft_strdup(tmp), n, redir_num);
	else if (line[0] == '>' && line[1] == '>' && shell->redir_error[n] != 1)
 		prepare_append(shell, ft_strdup(tmp), n, redir_num);
	return (0);
}

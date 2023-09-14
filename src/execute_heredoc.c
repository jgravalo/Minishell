#include  "../inc/minishell.h"

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

static char *here_loop(t_shell *shell, t_cmd **cmd, int *i, int start_line)
{	
	char *str;
	char *heredoc;

	while (1)
	{	
		printf("delimiter es %s\n", cmd[*i]->redir_x->path_arg->arg);
		str = readline("> ");
		printf("str es %s\n", str);
		if (ft_strcmp(str, cmd[*i]->redir_x->path_arg->arg) == 0)
			break;
		else if (str == NULL)
		{	
			write_heredoc_eof(shell, start_line);
			break;
		}
		str = ft_strjoin(str, "\n");
		heredoc = ft_strjoin(heredoc, str);
		shell->line_number++;
	}
	return (heredoc);
}

static void make_heredoc(t_shell *shell, t_cmd **cmd, int *i)
{	
	int start_line;
	char *heredoc;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	heredoc = ft_strdup("");
	start_line = shell->line_number;
	heredoc = here_loop(shell, cmd, i, start_line);
	printf("sale de hereloop\n");
	write(cmd[*i]->redir_x->fd, heredoc, ft_strlen(heredoc));
	close(cmd[*i]->redir_x->fd);
	cmd[*i]->redir_x->fd = open(shell->here_tmp, O_RDONLY);
	unlink(shell->here_tmp);
	free(heredoc);
	exit(0);
}

void heredoc(t_shell *shell, t_cmd **cmd, int *i)
{	
	pid_t	pid;
	int		status;
	t_redir	*ptr;

	ptr = cmd[*i]->redir_x;
	while(ptr)
	{	
		if (ptr->type == HERE)
		{	
			cmd[*i]->redir_x->fd = open(shell->here_tmp, O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
			pid = fork();
			if (pid > 0)
			{	
				signal(SIGINT, handle_signal);
				signal(SIGQUIT, handle_signal);
				waitpid(pid, &status, 0);
			}
			else if (pid == 0)
				make_heredoc(shell, cmd, i);
		}
		ptr = ptr->next;
	}
}
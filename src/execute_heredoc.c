/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:52:47 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 13:12:48 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 1;
		write(1, "\n", 1);
	}
	if (sig == SIGQUIT)
		return ;
}

static void	write_heredoc_eof(t_shell *shell, int start_line)
{
	write(2, "bash: warning: here-document at line ", 37);
	write(2, ft_itoa(start_line), ft_strlen(ft_itoa(shell->line_number)));
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, shell->delimiter, ft_strlen(shell->delimiter));
	write(2, "')\n", 3);
}

static char	*here_loop(t_shell *sh, t_cmd **cmd, int *i, int start_line)
{
	char	*str;
	char	*heredoc;

	heredoc = ft_strdup("");
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(str, cmd[*i]->red_x->arg->arg) == 0)
			break ;
		else if (str == NULL)
		{
			write_heredoc_eof(sh, start_line);
			break ;
		}
		str = ft_strjoin(str, "\n");
		heredoc = ft_strjoin(heredoc, str);
		sh->line_number++;
	}
	return (heredoc);
}

static void	make_heredoc(t_shell *sh, t_cmd **cmd, int *i)
{
	int		start_line;
	char	*heredoc;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	heredoc = ft_strdup("");
	start_line = sh->line_number;
	heredoc = here_loop(sh, cmd, i, start_line);
	write(cmd[*i]->red_x->fd, heredoc, ft_strlen(heredoc));
	close(cmd[*i]->red_x->fd);
	cmd[*i]->red_x->fd = open(sh->here_tmp, O_RDONLY);
	unlink(sh->here_tmp);
	free(heredoc);
	exit(0);
}

void	heredoc(t_shell *sh, t_cmd **cmd, int *i)
{
	pid_t	pid;
	int		status;
	t_redir	*ptr;

	ptr = cmd[*i]->red_x;
	while (ptr)
	{
		if (ptr->type == HERE)
		{
			cmd[*i]->red_x->fd = open(sh->here_tmp,
					O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
			pid = fork();
			if (pid > 0)
			{
				signal(SIGINT, handle_signal);
				signal(SIGQUIT, handle_signal);
				waitpid(pid, &status, 0);
			}
			else if (pid == 0)
				make_heredoc(sh, cmd, i);
		}
		ptr = ptr->next;
	}
}

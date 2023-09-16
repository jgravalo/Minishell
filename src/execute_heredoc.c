/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:52:47 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 10:20:22 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static char	*here_loop(t_shell *sh, t_redir *ptr, int start_line)
{
	char	*str;
	char	*heredoc;

	heredoc = ft_strdup("");
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(str, ptr->arg->arg) == 0)
			break ;
		else if (str == NULL)
		{
			write_heredoc_eof(sh, start_line, ptr->arg->arg);
			break ;
		}
		str = ft_strjoin(str, "\n");
		heredoc = ft_strjoin(heredoc, str);
		sh->line_number++;
	}
	return (heredoc);
}

static void	make_heredoc(t_shell *sh, t_redir *ptr)
{
	int		start_line;
	char	*heredoc;

	signal(SIGINT, exit_heredoc);
	signal(SIGQUIT, exit_heredoc);
	ptr->fd = open("/tmp/here_tmp",
			O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	heredoc = ft_strdup("");
	start_line = sh->line_number;
	heredoc = here_loop(sh, ptr, start_line);
	write(ptr->fd, heredoc, ft_strlen(heredoc));
	close(ptr->fd);
	free(heredoc);
	exit(0);
}

static void	parent(pid_t pid, t_redir *ptr)
{
	int		status;

	signal(SIGINT, parent_heredoc);
	signal(SIGQUIT, parent_heredoc);
	waitpid(pid, &status, 0);
	if (g_exit)
		return ;
	ptr->fd = open("/tmp/here_tmp", O_RDONLY);
	unlink("/tmp/here_tmp");
}

void	heredoc(t_shell *sh, t_cmd **cmd)
{
	int		i;
	pid_t	pid;
	t_redir	*ptr;

	i = 0;
	while (cmd[i])
	{
		ptr = cmd[i]->red_x;
		while (ptr)
		{
			if (ptr->type == HERE)
			{
				pid = fork();
				if (pid > 0)
					parent(pid, ptr);
				else if (pid == 0)
					make_heredoc(sh, ptr);
			}
			if (g_exit)
				return ;
			ptr = ptr->next;
		}
		i++;
	}
}

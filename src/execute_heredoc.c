/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:52:47 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 08:07:18 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	printf("proceso %d en make heredoc\n", getpid());
	signal(SIGINT, exit_heredoc);
	signal(SIGQUIT, exit_heredoc);
	heredoc = ft_strdup("");
	start_line = sh->line_number;
	heredoc = here_loop(sh, cmd, i, start_line);
	write(cmd[*i]->red_x->fd, heredoc, ft_strlen(heredoc));
	close(cmd[*i]->red_x->fd);
	free(heredoc);
	exit(0);
}

static int	parent(t_cmd **cmd, pid_t pid, t_redir *ptr, int *i)
{
	int		status;

	printf("proceso %d en parent heredoc\n", getpid());
	close(cmd[*i]->red_x->fd);
	signal(SIGINT, parent_heredoc);
	signal(SIGQUIT, parent_heredoc);
	waitpid(pid, &status, 0);
	if (g_exit)
	{
		printf("g exit %d, proceso %d sale\n", g_exit, getpid());
		exit(130);
	}
	ptr->fd = open("/tmp/here_tmp", O_RDONLY);
}

void	heredoc(t_shell *sh, t_cmd **cmd, int *i)
{
	pid_t	pid;
	t_redir	*ptr;

	ptr = cmd[*i]->red_x;
	while (ptr)
	{
		if (ptr->type == HERE)
		{
			ptr->fd = open("/tmp/here_tmp",
					O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
			pid = fork();
			if (pid > 0)
				parent(cmd, pid, ptr, i);
			else if (pid == 0)
				make_heredoc(sh, cmd, i);
		}
		ptr = ptr->next;
	}
}

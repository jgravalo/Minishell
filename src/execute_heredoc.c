/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:52:47 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:49:23 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

static int	here_aux(char *str, t_redir *ptr, int start_line)
{
	if (ft_strcmp(str, ptr->arg->arg) == 0)
	{
		free(str);
		return (1);
	}
	else if (str == NULL)
	{
		write_heredoc_eof(start_line, ptr->arg->arg);
		free(str);
		return (1);
	}
	return (0);
}

static char	*here_loop(t_shell *sh, t_redir *ptr, int start_line)
{
	char	*str;
	char	*heredoc;
	char	*tmp;
	char	*tmp2;

	heredoc = NULL;
	while (1)
	{
		str = readline("> ");
		tmp2 = str;
		if (here_aux(str, ptr, start_line))
			break ;
		str = ft_strjoin(str, "\n");
		free(tmp2);
		tmp2 = str;
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, str);
		free(tmp);
		free(tmp2);
		sh->line_number++;
	}
	return (heredoc);
}

static void	make_heredoc(t_shell *sh, t_redir *ptr)
{
	int					start_line;
	char				*heredoc;
	struct sigaction	sigint;

	ft_memset(&sigint, 0, sizeof(struct sigaction));
	sigint.sa_flags = SA_RESTART;
	sigint.sa_handler = exit_heredoc;
	sigaction(SIGINT, &sigint, NULL);
	signal(SIGINT, exit_heredoc);
	signal(SIGQUIT, exit_heredoc);
	ptr->fd = open("/tmp/here_tmp",
			O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	start_line = sh->line_number;
	heredoc = here_loop(sh, ptr, start_line);
	write(ptr->fd, heredoc, ft_strlen(heredoc));
	close(ptr->fd);
	free(heredoc);
	exit(g_exit);
}

static void	parent(pid_t pid, t_redir *ptr)
{
	int					status;
	struct sigaction	sigint;

	ft_memset(&sigint, 0, sizeof(struct sigaction));
	sigint.sa_flags = SA_RESTART;
	sigint.sa_handler = parent_heredoc;
	sigaction(SIGINT, &sigint, NULL);
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

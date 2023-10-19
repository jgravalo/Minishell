/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:52:47 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/19 16:10:38 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

static int	here_aux(char *str, t_redir *ptr)
{
	if (ft_strcmp(str, ptr->arg->arg) == 0)
	{
		free(str);
		return (1);
	}
	else if (str == NULL)
	{
		free(str);
		return (1);
	}
	return (0);
}

static char	*here_loop(t_redir *ptr)
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
		if (here_aux(str, ptr))
			break ;
		str = ft_strjoin(str, "\n");
		free(tmp2);
		tmp2 = str;
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, str);
		free(tmp);
		free(tmp2);
	}
	return (heredoc);
}

static void	make_heredoc(t_redir *ptr)
{
	char				*heredoc;
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = exit_heredoc;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	ptr->fd = open("/tmp/here_tmp",
			O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	heredoc = here_loop(ptr);
	ft_printf(ptr->fd, "%s", heredoc);
	close(ptr->fd);
	free(heredoc);
	exit(g_exit);
}

static void	parent(pid_t pid, t_redir *ptr)
{
	int					status;
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = parent_heredoc;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	waitpid(pid, &status, 0);
	if (g_exit)
		return ;
	ptr->fd = open("/tmp/here_tmp", O_RDONLY);
	unlink("/tmp/here_tmp");
}

void	heredoc(t_cmd **cmd)
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
					make_heredoc(ptr);
			}
			if (g_exit)
				return ;
			ptr = ptr->next;
		}
		i++;
	}
}

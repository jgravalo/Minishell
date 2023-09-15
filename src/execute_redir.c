/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:51:29 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 14:49:25 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	set_in(t_shell *shell, t_redir *ptr)
{
	if (ptr->type == IN)
	{
		ptr->fd = open(ptr->arg->arg, O_RDONLY);
		if (ptr->fd == -1)
		{
			shell->exit = cmd_error(ptr->arg->arg, errno, 1);
			return ;
		}
		dup2(ptr->fd, STDIN_FILENO);
		close(ptr->fd);
	}
}

static void	set_out(t_shell *shell, t_redir *ptr)
{
	if (ptr->type == OUT)
	{
		ptr->fd = open(ptr->arg->arg, O_RDWR | O_CREAT | O_TRUNC, 00644);
		if (ptr->fd == -1)
		{
			shell->exit = cmd_error(ptr->arg->arg, errno, 1);
			return ;
		}
		dup2(ptr->fd, STDOUT_FILENO);
		close(ptr->fd);
	}
}

static void	set_append(t_shell *shell, t_redir *ptr)
{
	if (ptr->type == OUT)
	{
		ptr->fd = open(ptr->arg->arg, O_RDWR | O_CREAT | O_APPEND, 00644);
		if (ptr->fd == -1)
		{
			shell->exit = cmd_error(ptr->arg->arg, errno, 1);
			return ;
		}
		dup2(ptr->fd, STDOUT_FILENO);
		close(ptr->fd);
	}
}

static void	set_redirs(t_shell *shell, t_cmd **cmd, int *i)
{
	t_redir	*ptr;
	int		error;

	error = 0;
	ptr = cmd[*i]->red_x;
	while (ptr)
	{
		set_in(shell, ptr);
		set_out(shell, ptr);
		set_append(shell, ptr);
		if (ptr->type == HERE)
		{
			dup2(ptr->fd, STDIN_FILENO);
			close(ptr->fd);
		}
		if (shell->exit)
			exit (shell->exit);
		ptr = ptr->next;
	}
}

void	execute_redir(t_shell *shell, t_cmd **cmd, int *i)
{
	heredoc(shell, cmd, i);
	set_redirs(shell, cmd, i);
}

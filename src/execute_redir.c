/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:51:29 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 08:27:43 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	set_in(t_shell *sh, t_cmd **cmd, t_redir *ptr, int *i)
{
	if (ptr->type == IN)
	{
		cmd[*i]->in_fd = open(ptr->arg->arg, O_RDONLY);
		if (cmd[*i]->in_fd == -1)
		{
			sh->exit = cmd_error(ptr->arg->arg, errno, 1);
			return (1);
		}
	}
	return (0);
}

static int	set_out(t_shell *sh, t_cmd **cmd, t_redir *ptr, int *i)
{
	if (ptr->type == OUT)
	{
		cmd[*i]->out_fd = open(ptr->arg->arg,
				O_RDWR | O_CREAT | O_TRUNC, 00644);
		if (cmd[*i]->out_fd == -1)
		{
			sh->exit = cmd_error(ptr->arg->arg, errno, 1);
			return (1);
		}
	}
	return (0);
}

static int	set_append(t_shell *sh, t_cmd **cmd, t_redir *ptr, int *i)
{
	if (ptr->type == APPEND)
	{
		cmd[*i]->out_fd = open(ptr->arg->arg, 
				O_RDWR | O_CREAT | O_APPEND, 00644);
		if (cmd[*i]->out_fd == -1)
		{
			sh->exit = cmd_error(ptr->arg->arg, errno, 1);
			return (1);
		}
	}
	return (0);
}

static int	set_redirs(t_shell *sh, t_cmd **cmd, int *i)
{
	t_redir	*ptr;
	int		error;

	error = 0;
	ptr = cmd[*i]->red_x;
	while (ptr)
	{
		if (set_in(sh, cmd, ptr, i))
			return (1);
		if (set_out(sh, cmd, ptr, i))
			return (1);
		if (set_append(sh, cmd, ptr, i))
			return (1);
		if (ptr->type == HERE)
		{	
			printf("entra en heredoc\n");
			cmd[*i]->in_fd = ptr->fd;
		}
		ptr = ptr->next;
	}
}

int	execute_redir(t_shell *sh, t_cmd **cmd, int *i)
{
	cmd[*i]->in_fd = -20;
	cmd[*i]->out_fd = -20;
	//heredoc(sh, cmd, i);
	if (set_redirs(sh, cmd, i))
		return (1);
	if (cmd[*i]->in_fd > -1)
	{	
		printf("tocamos stdin\n");
		sh->stdin_cpy = dup(STDIN_FILENO);
		dup2(cmd[*i]->in_fd, STDIN_FILENO);
		close(cmd[*i]->in_fd);
	}
	if (cmd[*i]->out_fd > -1)
	{
		sh->stdout_cpy = dup(STDOUT_FILENO);
		dup2(cmd[*i]->out_fd, STDOUT_FILENO);
		close(cmd[*i]->out_fd);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:10:58 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/27 11:54:18 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../inc/builtins.h"

static void	fork_cmd(t_shell *sh, t_cmd **cmd, int *i)
{
	(*i)++;
	sh->children++;
	cmd[*i]->pid = fork();
	if (cmd[*i]->pid > 0)
	{
		if (*i < sh->pipes)
			fork_cmd(sh, cmd, i);
	}
}

static void	recover_std(t_shell *sh)
{
	if (sh->stdin_cpy != -20)
		dup2(sh->stdin_cpy, STDIN_FILENO);
	if (sh->stdout_cpy != -20)
		dup2(sh->stdout_cpy, STDOUT_FILENO);
}

static int	no_pipe_built_in(t_shell *sh, t_cmd **cmd)
{
	if (!sh->pipes && check_builtin(cmd[0]->args))
	{
		sh->stdin_cpy = -20;
		sh->stdout_cpy = -20;
		if (execute_redir(sh, cmd, 0))
			return (1);
		builtin(sh, cmd, 0);
		recover_std(sh);
		return (1);
	}
	else
		return (0);
}

static void	child(t_shell *sh, t_cmd **cmd, int i)
{
	execute_pipes(sh, cmd, i);
	if (execute_redir(sh, cmd, i))
		exit(1);
	if (builtin(sh, cmd, i))
		exit(sh->exit);
	if (cmd[i]->args)
	{
		search(sh, cmd, i);
		execve(cmd[i]->path, cmd[i]->args, sh->envp);
	}
	else
		exit(0);
}

void	execute(t_shell *sh, t_cmd **cmd)
{
	int	i;

	i = -1;
	sh->children = 0;
	create_pipes(sh);
	heredoc(sh, cmd);
	if (g_exit)
		return ;
	if (no_pipe_built_in(sh, cmd))
		return ;
	fork_cmd(sh, cmd, &i);
	if (cmd[i]->pid == 0)
		child(sh, cmd, i);
	else
	{
		parent_close(sh);
		parent_wait(sh, cmd);
		if (sh->pipes)
			free(sh->p);
	}
}

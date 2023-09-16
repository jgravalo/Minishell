/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:10:58 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 07:59:57 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	create_pipes(t_shell *sh, t_cmd **cmd)
{
	int	i;

	i = 0;
	sh->p = (t_pipe *)malloc(sizeof(t_pipe) * (sh->pipes));
	while (i < sh->pipes)
	{
		pipe(sh->p[i].p);
		i++;
	}
	sh->children = 0;
}

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

static int	no_pipe_built_in(t_shell *sh, t_cmd **cmd, int *i)
{
	if (!sh->pipes && check_builtin(cmd[0]->args))
	{
		(*i)++;
		sh->stdin_cpy = -20;
		sh->stdout_cpy = -20;
		if (execute_redir(sh, cmd, i))
			return (1);
		builtin(sh, cmd, i);
		recover_std(sh);
		return (1);
	}
	else
		return (0);
}

void	execute(t_shell *sh, t_cmd **cmd)
{
	int	i;
	int	status;

	i = -1;
	printf("proceso %d entra en execute\n", getpid());
	if (no_pipe_built_in(sh, cmd, &i))
		return ;
	printf("proceso %d no entra en no pipe builtin\n", getpid());
	sh->children = 0;
	create_pipes(sh, cmd);
	fork_cmd(sh, cmd, &i);
	printf("proceso %d sale de fork,\n", getpid());
	if (cmd[i]->pid == 0)
	{
		execute_pipes(sh, cmd, i);
		if (execute_redir(sh, cmd, &i))
			exit(1);
		if (builtin(sh, cmd, &i))
			exit(sh->exit);
		search(sh, cmd, &i);
		execve(cmd[i]->path, cmd[i]->args, sh->envp);
	}
	else
	{
		parent_close(sh);
		parent_wait(sh, cmd);
	}
}

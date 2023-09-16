/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 07:32:45 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 10:19:55 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

void	exit_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("proceso %d sale\n", getpid());
		exit(1);
	}
	if (sig == SIGQUIT)
		return ;
}

void	parent_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("proceso %d coloca variable global\n", getpid());
		g_exit = 1;
	}
	if (sig == SIGQUIT)
		return ;
}

void	write_heredoc_eof(t_shell *sh, int start_line, char *delimiter)
{
	write(2, "bash: warning: here-document at line ", 37);
	write(2, ft_itoa(start_line), ft_strlen(ft_itoa(sh->line_number)));
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
}

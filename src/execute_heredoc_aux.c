/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 07:32:45 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 08:06:08 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	write_heredoc_eof(t_shell *shell, int start_line)
{
	write(2, "bash: warning: here-document at line ", 37);
	write(2, ft_itoa(start_line), ft_strlen(ft_itoa(shell->line_number)));
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, shell->delimiter, ft_strlen(shell->delimiter));
	write(2, "')\n", 3);
}


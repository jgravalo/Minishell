/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 07:32:45 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/14 09:51:48 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/libft.h"
#include "../inc/utils.h"

void	exit_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGQUIT)
		return ;
}

void	parent_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf(1, "\n", 1);
		g_exit = 1;
	}
	if (sig == SIGQUIT)
		return ;
}

void	write_heredoc_eof(int start_line, char *delimiter)
{
	ft_printf(2, "bash: warning: here-document at line ");
	ft_printf(2, "%d delimited by end-of-file ", start_line);
	ft_printf(2, "(wanted `%s')\n", delimiter);
}

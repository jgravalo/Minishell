/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 07:32:45 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/19 08:10:27 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
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
		write(1, "\n", 1);
		g_exit = 1;
	}
	if (sig == SIGQUIT)
		return ;
}

void	write_heredoc_eof(int start_line, char *delimiter)
{
	char	*tmp;

	tmp = ft_itoa(start_line);
	write(2, "bash: warning: here-document at line ", 37);
	write(2, tmp, ft_strlen(tmp));
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
	free(tmp);
}

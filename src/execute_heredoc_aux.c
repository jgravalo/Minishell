/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 07:32:45 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/24 12:57:34 by dtome-pe         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 11:42:34 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>

int g_exit = 0;

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}

static void	set_sig(struct sigaction *sigint, struct sigaction *sigquit)
{
	sigint->sa_flags = SA_RESTART;
	sigquit->sa_flags = SA_RESTART;
	sigint->sa_handler = handler;
	sigquit->sa_handler = handler;
	sigaction(SIGINT, sigint, NULL);
	sigaction(SIGQUIT, sigquit, NULL);
}

static int	check_null(char *str)
{
	if (str == NULL)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	return (0);
}

int	new_shell(t_shell *shell)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	ft_memset(&sigint, 0, sizeof(struct sigaction));
	ft_memset(&sigquit, 0, sizeof(struct sigaction));
	while (1)
	{
		g_exit = 0;
		set_sig(&sigint, &sigquit);
		shell->readline = readline("minishell> ");
		if (check_null(shell->readline))
			break ;
		add_history(shell->readline);
		lexer(shell, shell->readline);
		categorizer(shell->tok);
		parser(shell);
		expander(shell, shell->s_cmd);
		set_argv(shell->s_cmd);
		execute(shell, shell->s_cmd);
	}
	return (shell->exit);
}

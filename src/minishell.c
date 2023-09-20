/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/20 17:31:05 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include <readline/readline.h>

int	g_exit = 0;

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

int	shell_body(t_shell *sh)
{
	lexer(sh, sh->readline);
	categorizer(sh->tok);
	ft_printbothlst(sh->tok);
	if (reviser(sh->tok, sh) != 0)
	{
		add_history(sh->readline);
		sh->exit = 258;
		return (1);
	}
	add_history(sh->readline);
	parser(sh);
	expander(sh, sh->s_cmd);
	set_argv(sh->s_cmd);
	execute(sh, sh->s_cmd);
	return (0);
}

int	new_shell(t_shell *sh)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	ft_memset(&sigint, 0, sizeof(struct sigaction));
	ft_memset(&sigquit, 0, sizeof(struct sigaction));
	while (1)
	{
		g_exit = 0;
		set_sig(&sigint, &sigquit);
		sh->readline = readline("minishell> ");
		if (check_null(sh->readline))
			break ;
		if (quotes_errors(sh) != 0 || shell_body(sh) != 0)
			continue ;
		if (g_exit)
			sh->exit = 130;
		free_sh(sh);
	}
	return (sh->exit);
}

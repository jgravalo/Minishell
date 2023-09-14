/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/14 02:27:45 by theonewhokn      ###   ########.fr       */
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

static void set_interactive_sig(struct sigaction *sigint, struct sigaction *sigquit)
{
	sigint->sa_flags = SA_RESTART;
	sigquit->sa_flags = SA_RESTART;
	sigint->sa_handler = handler;
	sigquit->sa_handler = handler;
	sigaction(SIGINT, sigint, NULL);
	sigaction(SIGQUIT, sigquit, NULL);
}

int	new_shell(t_shell *shell)
{	
	struct sigaction sigint;
	struct sigaction sigquit;
	
	memset(&sigint, 0, sizeof(struct sigaction));//funcion prohibida. hacer las nuestra (cierto!)
	memset(&sigquit, 0, sizeof(struct sigaction));//funcion prohibida. hacer las nuestra
	while (1)
	{	
		g_exit = 0;
		set_interactive_sig(&sigint, &sigquit);
		shell->prompt = get_prompt(shell, shell->envp);
		shell->readline = readline("minishell> ");
		add_history(shell->readline);
		
		lexer(shell, shell->readline);
		categorizer(shell->tokens);
		//ft_printbothlst(shell->tokens);
		parser(shell);
/* 		printf("tras parser\n");
		ft_printcmd(shell->s_cmd); */
		expander(shell, shell->s_cmd);
		printf("tras expander\n");
		ft_printcmdargx(shell->s_cmd);
		quote_remove(shell->s_cmd);
		printf("tras quote remove\n");
		ft_printcmd(shell->s_cmd);
/* 		if (shell->readline == NULL)
		{	
			write(1, "exit\n", 5);
			break ;
		}
		if (shell->readline[0] != 0)
		{	
			//shell->readline = parse_quotes(shell->readline);
			if (parse_pipes(shell) != 0)
				continue ;
			shell->readline = expand_meta(shell, shell->readline, 0);
			if (ft_strlen(shell->readline) > 0)
				parse_pipex(shell);
			else
				shell->exit = 0;
			free(shell->readline);
		}
		free(shell->prompt);
		free(shell->user);
		shell->line_number++; */
	}
	free(shell->prompt);
	free(shell->user);
	free_m(shell->envp);
	free(shell->old_pwd);
	return (shell->exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/07 12:06:25 by theonewhokn      ###   ########.fr       */
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

int	new_shell(t_shell *shell)
{	
	shell->line_number = 1;
	while (1)
	{	
		g_exit = 0;
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		shell->prompt = get_prompt(shell, shell->envp);
		shell->readline = readline(shell->prompt);
		if (shell->readline == NULL)
		{	
			write(1, "exit\n", 5);
			break ;
		}
		if (shell->readline[0] != 0)
		{	
			shell->readline = parse_quotes(shell->readline);
			add_history(shell->readline);
			shell->readline = expand_meta(shell, shell->readline, 0);
			if (ft_strlen(shell->readline) > 0)
				parse_pipex(shell);
			else
				shell->exit = 0;
			free(shell->readline);
		}
		free(shell->prompt);
		free(shell->user);
		shell->line_number++;
	}
	free(shell->prompt);
	free(shell->user);
	free_m(shell->envp);
	return (shell->exit);
}

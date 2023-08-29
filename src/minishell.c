/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/29 17:09:42 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>

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
	//int fd;

	shell->line_number = 1;
	while (1)
	{	
		//dup2(fd, 1);
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
			//printf("line before expand meta es %s\n", shell->readline);
			shell->readline = expand_meta(shell, shell->envp);
			//shell->readline = parse_heredoc(shell->readline);
			if (ft_strlen(shell->readline) > 0)
				parse_pipex(shell);
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

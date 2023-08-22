/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/22 12:01:29 by theonewhokn      ###   ########.fr       */
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

	//fd = open("test", O_WRONLY);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{	
		//dup2(fd, 1);
		shell->prompt = get_prompt(shell->envp);
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
			shell->readline = expand_meta(shell, shell->readline, shell->envp);
			printf("line len after shell->readline es %ld\n", ft_strlen(shell->readline));
			//shell->readline = parse_heredoc(shell->readline);
			if (ft_strlen(shell->readline) > 0)
			{
				parse_pipex(shell);
				free(shell->readline);
			}
		}
		free(shell->prompt);
	}
	free(shell->prompt);
	free_m(shell->envp);
	return (shell->exit);
}


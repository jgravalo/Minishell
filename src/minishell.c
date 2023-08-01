/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/01 13:21:42 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>

static void empty_old_pwd(t_shell *shell)
{	
	shell->args = malloc(sizeof (char *) * 2);
	shell->args[0] = malloc (sizeof (char) * 6);
	shell->args[0] = "unset";
	shell->args[0] = malloc (sizeof (char) * 7);
	shell->args[1] = "OLDPWD";
	shell->args[2] = NULL;
	unset(shell);
	//free_m(shell->args);
	shell->args = malloc(sizeof (char *) * 2);
	shell->args[0] = malloc (sizeof (char) * 7);
	shell->args[0] = "export";
	shell->args[0] = malloc (sizeof (char) * 7);
	shell->args[1] = "OLDPWD";
	shell->args[2] = NULL;
	export(shell);
	//free_m(shell->args);
}

static void alloc_envp(t_shell *shell, char **envp)
{	
	int i;

	shell->envp = (char **)malloc(sizeof (char *) * (count_arr(envp) + 1));
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	empty_old_pwd(shell);
	/* shell->args[0] = "export";
	shell->args[1] = "OLDPWD";
	shell->args[2] = NULL;
	export(shell); */
}

static void	handler(int sig)
{	
	write(1, "\n", 1); // Move to a new line
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
}

int	new_shell(t_shell *shell)
{	
	char				*tmp;

	while (1)
	{	
		shell->prompt = get_prompt(shell->envp);
		signal(SIGINT, handler);
		shell->readline = readline(shell->prompt);
		if (shell->readline == NULL)
		{	
			write(1, "exit\n", 5);
			break ;
		}
		if (shell->readline[0] != 0)
		{	
			shell->readline = parse_quotes(shell->readline);
			shell->readline = expand_meta(shell, shell->readline, shell->envp); // implementar parseo single/double quotes (metachars dependen de ellas)
			//printf("%s\n", shell->readline);
			//shell->readline = parse_heredoc(shell->readline);  seguramente hay que implementarlo donde el redir, para que no se añada a la historia
			add_history(shell->readline);
			parse_pipex(shell);
			free(shell->readline);
		}
		free(shell->prompt);
	}
	free(shell->prompt);
	free_m(shell->envp);
	return (shell->exit);
}

int	main(int argc, char **argv, char **envp)
{	
	t_shell				shell;

	alloc_envp(&shell, envp);
	if (!argc && !argv && !envp)
		return (0);
	new_shell(&shell);
	return (shell.exit);
}	

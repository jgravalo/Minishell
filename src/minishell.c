/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/28 11:01:47 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>

void	test_pipe(t_pipe *p)
{
	char	buffer[17];

	read(p->p[0], buffer, 17);
	write(1, "<<<", 3);
	write(1, buffer, 17);
	write(1, ">>>", 3);
	write(1, "\n", 1);
}

/*
int parse_pipex(char *line, char **envp)
{
	char	**pipes;
	int		i;
	int		pipex;
	int		exit;
	t_pipe	*p;

	pipex = count_ascii(line, '|'); 
	pipes = ft_split(line, '|');
	if (pipex == 0)
		exit = parse_line(pipes[0], envp, NULL, NULL); //sin pipe
	else 
	{
		p = (t_pipe *)malloc(sizeof(t_pipe) * (pipex + 1));
		pipe(p[0].p);
		exit = parse_line(pipes[0], envp, NULL, &p[0]); //primer pipe
		close(p[0].p[1]); // cierras la salida/escritura del pipe
		i = 1;
		while (pipex > 1 && pipes[i + 1])
		{
			pipe(p[i].p);
			exit = parse_line(pipes[i], envp, &p[i - 1], &p[i]);// pipe intermedio
			close(p[i - 1].p[0]);
			close(p[i].p[1]); // cierras la salida/escritura del pipe
			i++;
		}
		exit = parse_line(pipes[i], envp, &p[i - 1], NULL); //ultimo pipe
		close(p[i - 1].p[0]); // cierras la entrada/lectura del pipe
	}
	return (exit);
}
*/

/*
int main(int argc, char **argv, char **envp)
{
	char	*c;
	int		exit;
//	t_hist	history;

	if (!argc && !argv && !envp)
		return (0);
	while (1)
	{
		c = readline("jgravalo> ");
//		write(1, "jgravalo> ", 10);
//		c = get_next_line(0);
//		write(1,  "aqui\n", 5);
//		rl_on_new_line();
//		if (ft_strcmp(c, "") == 0)
		if (ft_strlen(c) == 0)
		{
			write(1,  "aqui\n", 5);
//			rl_on_new_line();
			continue;
		}
//		write(1,  "aqui\n", 5);
		add_history(c);

//		write(1, "line = <", 8);
//		write(1, c, ft_strlen(c));
//		write(1, ">\n", 2);
		
		exit = parse_pipex(c, envp);
		free(c);
		c = NULL;
	}
	return (exit);
}
*/

static char **alloc_envp(char **envp)
{	
	char **envpcpy;
	int i;

	envpcpy = (char **)malloc(sizeof (char *) * (count_arr(envp) + 1));
	i = 0;
	while (envp[i])
	{
		envpcpy[i] = ft_strdup(envp[i]);
		i++;
	}
	envpcpy[i] = NULL;
	return (envpcpy);
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
			shell->readline = expand_meta(shell->readline, shell->envp); // implementar parseo single/double quotes (metachars dependen de ellas)
			shell->readline = parse_heredoc(shell->readline);
			add_history(shell->readline);
			parse_pipex(shell->readline, shell);
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

	shell.envp = alloc_envp(envp);
	if (!argc && !argv && !envp)
		return (0);
	new_shell(&shell);
	return (0);
}	

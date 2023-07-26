/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:48 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 08:51:25 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static void	handler(int sig)
{
	if (sig == SIGINT)
		return ;
	if (sig == SIGQUIT)
		return ;
}

static char**	init_envp(char **envp)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (count_arr(envp) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{	
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	new_shell(char **envp)
{
	char				*c;
	char				*tmp;
	int					exit_code;
	char 				*prompt;
	//char **envpcpy;
	
	//envpcpy = init_envp(envp);
	while (1)
	{	
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
/* 		prompt = get_prompt(envp);
		write(1, prompt, 500);
		c = readline(prompt); */
		c = readline(get_prompt(envp));
///		write(1, "aqui\n", 5);
		if (c == NULL)
		{	
			write(1, "exit\n", 6);
			free(prompt);
			exit(1);
		}
		if (c[0] != 0)
		{	
			//tmp = expand_meta(c, envp); // implementar parseo single/double quotes (metachars dependen de ellas)
			//c = parse_heredoc(tmp);
			add_history(c);
			exit_code = parse_pipex(c, envp);
			free(c);
		}
		free(prompt);
	}
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	if (!argc && !argv && !envp)
		return (0);
	new_shell(envp);
}

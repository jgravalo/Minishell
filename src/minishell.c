#include "../inc/minishell.h"

void test_pipe(t_pipe *p)
{
//	write(p->p[1], "el pipe funciona\n", 17);
	char buffer[17];
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

static void handler(int sig) 
{	
	if (sig == SIGINT)
    	write(1, "\njgravalo> ", 11);
	if (sig == SIGQUIT)
	{	
		return ;
	}
}
  
int new_shell(char **envp)
{	
	char				*c;
	int					exit_code;
	char 				**tokens;

	while (1)
	{	
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		c = readline("jgravalo> ");
		c = parse_heredoc(c); 
		if (c == NULL)
		{	
			write(1, "exit\n", 6);
			exit(1);
		}
		if (c[0] != 0)
		{	
			add_history(c);
			tokens = lexer(c); // creo recomendable empezar desde un lexer ya que tendriamos todos los simbolos en un array.
			//ft_printarr(tokens); // funcion que imprime el array de tokens, para debugear.
			exit_code = parse_pipex(c, envp);
			free(c);
		}
	}
		return (exit_code);
}

int main(int argc, char **argv, char **envp)
{	
	if (!argc && !argv && !envp)
		return (0);
	new_shell(envp);		
}


#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../inc/minishell.h"

int	parse_line(char *line, char **envp, t_pipe *in, t_pipe *out)
//int	parse_line(char *line, char **envp)
{
	char	**args;
	char	*cmd;
	pid_t	pid;
//	t_pipe	p;
	int		exit;
	pid = fork();
	if (pid > 0)
		exit = set_signals(pid, envp);
	if (pid == 0)
	{
		//fd = check_redir(args); //si hay redireccion, borrarla de la linea
		if (in != NULL)
		{
			dup2(in->p[0], 0);
			close(in->p[0]);
			close(in->p[1]);
//			test_pipe(in);
		}
		if (out != NULL)
		{
			dup2(out->p[1], 1);
			close(out->p[0]);
			close(out->p[1]);
		}
		dup2(1, 2);
		args = ft_split_marks(line, ' ');
		cmd = file_cmd(args[0], envp);
		execve(cmd, args, envp);
	}
	exit = WEXITSTATUS(exit);
	return (exit);
}

int parse_pipex(char *line, char **envp)
{
	char	**pipes;
	int		i;
	int		pipex;
	int		exit;
	t_pipe	*p;

	pipex = count_ascii(line, '|'); 
//	t_pipe	p[pipex];
//	printf("n_pipes = %d\n", pipex);
	pipes = ft_split(line, '|');
	if (pipex == 0)
		exit = parse_line(pipes[0], envp, NULL, NULL); //sin pipe
	else 
	{
		p = (t_pipe *)malloc(sizeof(t_pipe) * (pipex + 1));
		pipe(p[0].p);
		exit = parse_line(pipes[0], envp, NULL, &p[0]); //primer pipe
//		test_pipe(&p[0]);
		close(p[0].p[1]); // cierras la salida/escritura del pipe
		i = 1;
		while (pipex > 1 && pipes[i + 1])
		{
			pipe(p[i].p);
//			test_pipe(&p[i - 1]);
			exit = parse_line(pipes[i], envp, &p[i - 1], &p[i]);// pipe intermedio
//			test_pipe(&p[i]);
			close(p[i - 1].p[0]);
			close(p[i].p[1]);
			i++;
		}
		exit = parse_line(pipes[i], envp, &p[i - 1], NULL); //ultimo pipe
		close(p[i - 1].p[0]);
	}
	return (exit);
}

static void handler(int sig) 
{	
	if (sig == SIGINT)
    	write(1, "\njgravalo> ", 11);
	if (sig == SIGQUIT)
	{	
		printf("entra en quit\n");
		return ;
	}
}
  
int new_shell(char **envp)
{	
	char				*c;
	int					exit_code;

	while (1)
	{	
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		c = readline("jgravalo> ");
		if (c == NULL)
		{	
			write(1, "exit\n", 6);
			exit(1);
		}
		if (c[0] != 0)
		{	
			add_history(c);
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


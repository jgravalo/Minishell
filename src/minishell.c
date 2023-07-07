#include "../inc/minishell.h"

//int	search_redir(char **args)

int	check_redir(char **args, int type)
{
	int fd;
	int i;

	i = 0;
	while (args[i])
	{
		if (type == 0 && ft_strcmp(args[i], ">"))
			fd = open(args[i + 1], O_RDWR | O_CREAT | O_TRUNC, 00644); // > salida
		if (ft_strcmp(args[i], ">>"))
			fd = open(args[i + 1], O_RDWR | O_CREAT | O_APPEND, 00644); // >> salida
		if (ft_strcmp(args[i], "<"))
			fd = open(args[i + 1], O_RDONLY); // < entrada
//		if (ft_strcmp(args[i], "<<"))
		i++;
	}
	return (fd);
}

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

int	parse_line(char *line, char **envp, t_pipe *in, t_pipe *out)
//int	parse_line(char *line, char **envp)
{
	char	**args;
	char	*cmd;
	pid_t	pid;
//	t_pipe	p;
	int		exit;
/*
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
*/
//	line = check_vars(line, envp);
//	write(1, line, ft_strlen(line));
//	write(1, "\n", 1);
//	args = ft_split_marks(line, ' ');
	/*
	int i;
	for (i = 0; args[i]; i++)
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, ", ", 2);
	}
	write(1, "\n", 1);
	*/
//	ft_strcmp(tmp, (char *){27, 91, 65});
//	exit = built_ins(args, envp);
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
//		dup2(1, 2);
		args = ft_split_marks(line, ' ');
		cmd = file_cmd(args[0], envp);
		execve(cmd, args, envp);
	}
//	test_pipe(out);
	waitpid(pid, &exit, 0);
	exit = WEXITSTATUS(exit);
	return (exit);
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
int parse_pipex(char *line, char **envp)
{	
	t_shell shell;
	int		i;

	shell.pipex = count_ascii(line, '|'); 
	shell.pipes = ft_split(line, '|');
	if (shell.pipex == 0)
		shell.exit = parse_line(shell.pipes[0], envp, NULL, NULL); //sin pipe
	else 
	{
		shell.p = (t_pipe *)malloc(sizeof(t_pipe) * (shell.pipex + 1));
		pipe(shell.p[0].p);
		shell.exit = parse_line(shell.pipes[0], envp, NULL, &shell.p[0]); //primer pipe
		close(shell.p[0].p[1]); // cierras la salida/escritura del pipe
		i = 1;
		while (shell.pipex > 1 && shell.pipes[i + 1])
		{
			pipe(shell.p[i].p);
			shell.exit = parse_line(shell.pipes[i], envp, &shell.p[i - 1], &shell.p[i]);// pipe intermedio
			close(shell.p[i - 1].p[0]);
			close(shell.p[i].p[1]);
			i++;
		}
		shell.exit = parse_line(shell.pipes[i], envp, &shell.p[i - 1], NULL); //ultimo pipe
		close(shell.p[i - 1].p[0]);
	}
	return (shell.exit);
}

int parse_ands(char *line, char **envp)
{
	char	**ands;
	int		i;
	int		exit;

	ands = ft_split(line, '&');//modificarlo para que parta con strings
	i = 0;
	while (ands[i])
	{
		exit = parse_pipex(ands[i], envp);
		i++;
	}
	return (exit);
}

int parse_ors(char *line, char **envp)
{
	char	**ors;
	int		i;
	int		exit;

	ors = ft_split(line, '|');//modificarlo para que parta con strings
	i = 0;
	while (ors[i])
	{
		exit = parse_ands(ors[i], envp);
		if (exit == 0)
			break ;
		i++;
	}
	return (exit);
}
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

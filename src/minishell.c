#include "../inc/minishell.h"

//int	search_redir(char **args)

int	check_redir(char **args, int type)
{
	int fd;
	int i;

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

int	parse_line(char *line, char **envp, t_pipe *in, t_pipe *out)
//int	parse_line(char *line, char **envp)
{
	char	**args;
	char	*cmd;
	pid_t	pid;
	t_pipe	p;
	int		exit;

//	write(1, line, ft_strlen(line));
//	write(1, "\n", 1);
//	line = check_vars(line, envp);
//	write(1, line, ft_strlen(line));
//	write(1, "\n", 1);
	args = ft_split_marks(line, ' ');
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

	write(p[1], "el pipe funciona\n", 17);
	char buffer[17];
	read(p[0], buffer, 17);
	write(1, buffer, 17);

	if (!in)
		p.fdin = 0;
	else
		p.fdin = in->p[0];
	if (!out)
		p.fdout = 1;
	else
		p.fdout = out->p[1];
	pid = fork();
	if (pid == 0)
	{
		//fd = check_redir(args); //si hay redireccion, borrarla de la linea

		/*
		if (in)
			dup2(in->p[0], 0);
		if (out)
			dup2(out->p[1], 1);
		*/
		dup2(p.fdin, 0);
		dup2(p.fdout, 1);
		cmd = file_cmd(args[0], envp);
		execve(cmd, args, envp);
	}
	waitpid(pid, &exit, 0);
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
	pipes = ft_split(line, '|');
	if (pipex > 0)
	{
		p = (t_pipe *)malloc(sizeof(t_pipe) * (pipex + 1));
		pipe(p[0].p);
		exit = parse_line(pipes[0], envp, NULL, &p[0]); //primer pipe
	}
	else 
		exit = parse_line(pipes[0], envp, NULL, NULL); //sin pipe
	i = 1;
	while (pipex > 1 && pipes[i])
	{
		pipe(p[i].p);
		exit = parse_line(pipes[i], envp, &p[i - 1], &p[i]);// pipe intermedio
		i++;
	}
	if (pipex > 0)
	{
		exit = parse_line(pipes[i], envp, &p[i - 1], NULL); //ultimo pipe
	}
	return (exit);
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

int main(int argc, char **argv, char **envp)
{
	char	*c;
	int		exit;
//	t_hist	history;

	if (!argc && !argv && !envp)
		return (0);
	while (1)
	{
//		write(1, "jgravalo> ", 10);
		c = readline("jgravalo> ");
//		c = get_next_line(0);
//		make_history(&history, c);
//		print_history(&history);
	
		write(1, "line = |", 8);
		write(1, c, ft_strlen(c));
		write(1, "|\n", 2);
		
		exit = parse_pipex(c, envp);
//		parse_line(c, envp);
		free(c);
	}
//	print_history(&history);
	return (exit);
}

#include "../inc/minishell.h"

int	parse_line(char *line, char **envp)
{
	char	**args;
	char	*cmd;
	pid_t	pid;

	write(1, line, ft_strlen(line));
	check_vars(line, envp);
	write(1, line, ft_strlen(line));
	args = ft_split_marks(line, ' ');
	//fd = check_redir(); //si hay redireccion, borrarla de la linea
	//
	int i;
	for (i = 0; args[i]; i++)
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, ", ", 2);
	}
	write(1, "\n", 1);
	//
//	ft_strcmp(tmp, (char *){27, 91, 65});
	
	pid = fork();
	if (pid == 0)
	{
//		dup2(fdin, 0);
//		dup2(fdout, 1);
		cmd = file_cmd(args[0], envp);
		execve(cmd, args, envp);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int parse_pipex(char *line, char **envp)
{
	char	**pipes;
	int		i;
//	t_pipe	*p;

	pipes = ft_split(line, '|');
//	parse_line(pipes[0], envp); //primer pipe
	i = 0;
	while (pipes[i])
	{
//		pipe[p];
		parse_line(pipes[i], envp);
		i++;
	}
//	parse_line(pipes[i], envp);
	return (0);
}

int parse_ands(char *line, char **envp)
{
	char	**ands;
	int		i;

	ands = ft_split(line, '&');//modificarlo para que parta con strings
	i = 0;
	while (ands[i])
	{
		parse_pipex(ands[i], envp);
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	*c;
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
		
		parse_pipex(c, envp);
//		parse_line(c, envp);
		free(c);
	}
//	print_history(&history);
	return (0);
}

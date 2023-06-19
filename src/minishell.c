#include "../inc/minishell.h"

int	parse_line(char *line, char **envp)
{
	char	**args;
	char	*cmd;
	pid_t	pid;

	if (!envp)
		return (0);
	//check_redir(); //si hay redireccion, borrarla de la linea
	args = ft_split(line, ' ');
	
	int i;
//	for (i = 0; i < 3; i++)
	for (i = 0; args[i]; i++)
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, ",", 1);
	}
	write(1, "\n", 1);
	
	
//	cmd = args[0];
//	cmd = "/bin/echo";
	cmd = file_cmd(args[0], envp);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, args, envp);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char *c;

	if (!argc && !argv && !envp)
		return (0);
	while (1)
	{
		write(1, "jgravalo>", 9);
		c = get_next_line(0);
//		c = readline(NULL);
		/*
		write(1, "line = |", 8);
		write(1, c, ft_strlen(c));
		write(1, "|\n", 2);
		*/
		parse_line(c, envp);
		free(c);
	}
	 return (0);
}

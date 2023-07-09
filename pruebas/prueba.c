#include"inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	int p1[2];
	int p2[2];
	char	*cmd1 = "ls";
	char	*cmd2 = "wc";
	char	*cmd3 = "cat";
	pid_t pid1 = fork();
	pid_t pid2 = fork();
	pid_t pid3 = fork();

	pipe(p1);
	pipe(p2);
	if (pid1 == 0)
	{
		dup2(p1[1], 1);
		execve(file_cmd(cmd1, envp), ft_split(cmd1, ' '), envp);
	}
	if (pid2 == 0)
	{
		dup2(p1[0], 0);
		dup2(p2[1], 1);
		execve(file_cmd(cmd2, envp), ft_split(cmd2, ' '), envp);
	}
	if (pid3 == 0)
	{
		dup2(p2[0], 0);
		execve(file_cmd(cmd3, envp), ft_split(cmd3, ' '), envp);
	}
	wait(NULL);
	if (!argc && !argv)
		return 0;
	return (0);
}

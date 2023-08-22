#include "../inc/minishell.h"

static char *get_hostname(void)
{	
	int		pipefd[2];
	char	buf[256];
	char	*argv[2];
	char 	*host;
	pid_t 	pid;

	argv[0] = "hostname";
	argv[1] = NULL;
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (NULL);
	}
	if (pid > 0)
	{
		close(pipefd[1]);
		buf[read(pipefd[0], buf, sizeof (buf) - 1)] = '\0';
		close(pipefd[0]);
		host = ft_strdup(buf);
		host[ft_strlen(host) - 1] = '\0';
		return (host);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execve("/bin/hostname", argv, NULL);
		return (NULL);
	}
	return (NULL);
}

static char *put_home(char *cwd, int home_len)
{
	char *str1;
	char *home;

	str1 = ft_strdup(&cwd[home_len]);
	home = ft_strjoin("~", str1);
	free(str1);
	free(cwd);
	return (home);
}

static char *get_pwd(void)
{
	int		pipefd[2];
	char	buf[256];
	char	*argv[2];
	char 	*host;
	pid_t 	pid;

	argv[0] = "pwd";
	argv[1] = NULL;
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (NULL);
	}
	if (pid > 0)
	{
		close(pipefd[1]);
		buf[read(pipefd[0], buf, sizeof (buf) - 1)] = '\0';
		close(pipefd[0]);
		host = ft_strdup(buf);
		host[ft_strlen(host) - 1] = '\0';
		return (host);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execve("/bin/pwd", argv, NULL);
		return (NULL);
	}
	return (NULL);
}

static char *get_cwd(char **envp, char *user)
{	
	static char *home = NULL;
	char *cwd;
	int home_len;

	cwd = get_pwd();
	if (search_var_line("HOME", envp) != NULL)
	{	
		home = search_var_line("HOME", envp);
		ft_strchr(home, '=');
		home_len = ft_strlen(home);
		if (ft_strncmp(cwd, home, home_len) == 0)
			return (put_home(cwd, home_len));
		else
			return (cwd);
	}
	else
		return (cwd);
}

static char *get_user(char *prompt)
{
	int		pipefd[2];
	char	buf[256];
	char	*argv[2];
	pid_t 	pid;

	argv[0] = "whoami";
	argv[1] = NULL;
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (NULL);
	}
	if (pid > 0)
	{
		close(pipefd[1]);
		buf[read(pipefd[0], buf, sizeof (buf) - 1)] = '\0';
		close(pipefd[0]);
		prompt = ft_strdup(buf);
		prompt[ft_strlen(prompt) - 1] = '\0';
		return (prompt);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execve("/usr/bin/whoami", argv, NULL);
		return (NULL);
	}
	return (NULL);
}

char *get_prompt(t_shell *shell, char **envp)
{	
	char 	*prompt;
	char 	*host;
	char	*dir;


	if (search_var_line("PS1", envp) != NULL)
	{	
		prompt = ft_strdup(search_var_line("PS1", envp));
		return (prompt);
	}
	else
	{
		prompt = get_user(prompt);
		shell->user = get_user(prompt);
		prompt = prompt_join(prompt, "@");
		host = get_hostname();
		prompt = prompt_join(prompt, host);
		free(host);
		prompt = prompt_join(prompt, ":");
		dir = get_cwd(envp, shell->user);
		prompt = prompt_join(prompt, dir);
		prompt = prompt_join(prompt, "$ ");
		return (prompt);
	}
}
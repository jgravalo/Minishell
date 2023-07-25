#include "../inc/minishell.h"

static char *get_hostname(void)
{	
	int fd;
	char buf[256];
	int ret;
	int i;

	i = 0;
	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
	{
		printf("open error\n");
		return (NULL);
	}
	ret = read(fd, buf, 0);
	if (ret < 0)
	{
		printf("read error\n");
		return (NULL);
	}
	ret = read(fd, buf, sizeof (buf));
	close (fd);
	buf[ret - 1] = '\0';	
	return (ft_strdup(buf));
}

static char *put_home(char *cwd, int home_len)
{
	char *str1;
	char *home;

	str1 = ft_strdup(&cwd[home_len]);
	home = ft_strjoin("~", str1);
	free (str1);
	return (home);
}

static char *get_cwd(char **envp)
{
	char *cwd;
	char *home;
	int home_len;

	cwd = search_var("PWD", envp);
	home = search_var("HOME", envp);
	ft_strchr(home, '=');
	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) == 0)
	{
		home = put_home(cwd, home_len);
		return (home);
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
	}
}

char *get_prompt(char **envp)
{	
	char 	*prompt;
	char 	*host;
	char	*dir;

	prompt = search_var("PS1", envp);
	if (prompt != NULL)
		printf("%s ", prompt);
	else
	{
		prompt = get_user(prompt);
		prompt = prompt_join(prompt, "@");
		host = get_hostname();
		prompt = prompt_join(prompt, host);
		free(host);
		prompt = prompt_join(prompt, ":");
		dir = get_cwd(envp);
		prompt = prompt_join(prompt, dir);
		free(dir);
		prompt = prompt_join(prompt, "$ ");
	}
}
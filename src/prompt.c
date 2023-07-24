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

char *get_prompt(char **envp)
{	
	char *	prompt;

	prompt = search_var("PS1", envp);
	if (prompt != NULL)
		printf("%s ", prompt);
	else
	{
		prompt = search_var("USER", envp);
		prompt = ft_strjoin(prompt, "@");
		prompt = ft_strjoin(prompt, get_hostname());
		prompt = ft_strjoin(prompt, ":");
		prompt = ft_strjoin(prompt, get_cwd(envp));
		prompt = ft_strjoin(prompt, "$ ");
	}
}
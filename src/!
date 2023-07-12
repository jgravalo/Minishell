#include "../inc/minishell.h"

char	*meta_str(char const *s, char c, int *n)
{
	int		i;
	char	*new;

	i = 0;
	while (*s && *s != c && ++i)
	{
		if (*s == '\'' && ++s && ++i)
			while (*s && *s != '\'' && ++i)
				s++;	
		s++;
	}
	new = ft_substr(s - i, 0, i);
	*n = i;
	return (new);
}

int	words_meta(const char *s, char c)
{
	int	j;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
				s++;
			j++;
		}
		else
			++s;
	}
	return (j);
}

char	**ft_split_meta(char const *s, char c)
{
	int		j;
	int		i;
	char	**res;

	res = (char **) malloc((words_meta(s, c) * (sizeof(char *))) + 8);
	if (!res || !s)
		return (0);
	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			i = 0;
			res[j++] = meta_str(s, c, &i);
			s += i;
		}
		else
			++s;
	}
	res[j++] = NULL;
	return (res);
}

void	get_var(t_var *p, char **envp, int n)
{
	int		j;

	while (p->tmp[n])
	{
		j = 0;
		while (p->tmp[n][j] &&
			((p->tmp[n][j] >= 'a' && p->tmp[n][j] <= 'z') ||
			(p->tmp[n][j] >= 'A' && p->tmp[n][j] <= 'Z') ||
			(p->tmp[n][j] >= '0' && p->tmp[n][j] <= '9')))
			j++;
		p->var = ft_substr(p->tmp[n], 0, j);
		p->exp = search_var(p->var, envp);
		p->c = ft_strjoin(p->new, p->exp);
		p->tmp[n] += j;
		p->new = ft_strjoin(p->c, p->tmp[n]);
		n++;
	}
}
char	*expand_meta(char *line, char **envp)
{
	t_var	p;
	int		n;

	p.tmp = ft_split_meta(line, '$');
	p.new = p.tmp[0];
	n = 1;
	if (line[0] == '$')
	{
		p.new = NULL;
		n = 0;
	}
	get_var(&p, envp, n);	
	return (p.new);
}
/*
int main(int argc, char **argv, char **envp)
{
	if (argc > 1 && argv)
		return (0);
	while (1)
	{
		char *c = readline("> ");
		c = expand_meta(ft_strdup(c), envp);
		printf("|%s|\n", c);
	}
	return (0);
}*/

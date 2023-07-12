#include "../inc/minishell.h"

typedef struct	s_var
{
	char	*new;
	char	*exp;
	char	*var;
	int		i;
	int		j;
	int		n;
}	t_var;


int len_expand(char *line, char **envp)
{
	t_var p;
/*
	char *p.exp;
	char *p.var;
	[p.i]nt i;
	[p.i]nt n;
*/

	p.i = 0;
	while(line[p.i])
	{
		if (line[p.i] == '\'' && ++p.i)
			while (line[p.i] && line[p.i] != '\'')
				p.i++;
		if (line[p.i] == '$' && ++p.i)
		{
			p.n = 0;
			while (line[p.i] && line[p.i] != ' ' && ++p.i)
				p.n++;
			p.var = ft_substr(line, p.i - p.n, p.n);
			p.exp = search_var(p.var, envp);
			printf("aqui\n");
			p.i += p.n;
			free(p.var);
//			free(p.exp);
		}
		p.i++;
	}
	return (p.i);
}

char *expand_var(char *line, char **envp)
{
	t_var p;
/*
	char *p.new;
	char *p.exp;
	char *p.var;
	[p.i]nt i;
	[p.i]nt [p.j];
	[p.i]nt n;
*/

	p.new = (char *)malloc(sizeof(char) * len_expand(line, envp) + 1);
	p.i = 0;
	p.j = 0;
	while(line[p.i])
	{
		printf("line[i] = %c\n", line[p.i]);
		if (line[p.i] == '\'' && ++p.i)
			while (line[p.i] && line[p.i] != '\'')
				p.i++;
		else if (line[p.i] == '$' && ++p.i)
		{
			p.n = 0;
			while (line[p.i] && line[p.i] != ' ' && ++p.i)
				p.n++;
			p.var = ft_substr(line, p.i - p.n, p.n);
			p.exp = search_var(p.var, envp);
			printf("new = %s\n", p.new);
//			printf("i = %d\n", p.i);
			ft_strcat(p.new, p.exp);
			p.i += p.n;
			p.i += ft_strlen(p.var);
//			printf("i = %d\n", p.i);
//			printf("line = %c\n", line[p.i]);
			printf("new = %s\n", p.new);
			p.j += ft_strlen(p.exp);
			free(p.var);
//			free(p.exp);
		}
//		if (line[p.i])
		else
			p.new[p.j] = line[p.i];
		p.j++;
		p.i++;
	}
	printf("new = %s\n", p.new);
	return (p.new);
}


int main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (0);
	char *c = expand_var(ft_strdup(argv[1]), envp);
	printf("|%s|\n", c);
	return (0);
}

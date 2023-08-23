/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:38:46 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/23 10:04:08 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*meta_str(char const *s, char c, int *n)
{
	int		i;
	char	*new;

	i = 0;
	while (*s && *s != ' ' && ++i)
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
		//printf("enter loop, *s es %c\n", *s);
		while (*s != c && *s != '\0')
			++s;
		if (*s == '\0')
			break;
		++s;
		//printf("*s es %c\n", *s);
		if (*s != c)
		{
			i = 0;
			res[j++] = meta_str(s, c, &i);
			//printf("substr is %s, i es %d\n", res[0], i);
			s += i;
			//printf("*s es %s\n", s);
		}
		else
			++s;
	}
	res[j++] = NULL;
	return (res);
}

static char	*get_var(t_shell *shell, t_var *p, char *new_line, int n)
{
	int		j;
	int 	i;
	int start;

	printf("ptmp0 es %s y len es %ld\n, new line es %s, y len de new line es %ld\n", p->tmp[n], ft_strlen(p->tmp[n]), new_line, ft_strlen(new_line));
	i = 0;
	start = 0;
	while (new_line[i] && p->tmp[n])
	{	
		printf("start is %c and i es %d\n", new_line[start], i);
		while (new_line[i] != '$')
			i++;
		printf("entra aqui, n es %d\n", n);
		j = 0;
		if (p->tmp[n][j] == '?') //exit code
		{	
			j++;
			p->exp = ft_itoa(shell->exit);
		}
		else
		{	
			if (search_var_line(p->tmp[n], shell->envp) == NULL)
			{	
				p->var = ft_strdup("");
				p->exp = ft_strdup("");
				j += ft_strlen(p->tmp[n]);
			}
			else
			{
				while (p->tmp[n][j] &&
					((p->tmp[n][j] >= 'a' && p->tmp[n][j] <= 'z') ||
					(p->tmp[n][j] >= 'A' && p->tmp[n][j] <= 'Z') ||
					(p->tmp[n][j] >= '0' && p->tmp[n][j] <= '9')))
					j++;
				p->var = ft_substr(p->tmp[n], 0, j);
				p->exp = search_var_line(p->var, shell->envp);
				printf("p->exp es %s\n", p->exp);
			}
		}
		printf("start is %d, and i is %d, before substr\n", start, i);
		printf("newline substr is %s\n", ft_substr(new_line, start, i));
		p->c = ft_strjoin(ft_substr(new_line, start, i - start), p->exp);
		printf("p->c es %s\n", p->c);
		p->new = ft_strjoin(p->new, p->c);
		/* printf("p->c es %s\n", p->c);
		p->tmp[n] += j;
		p->new = ft_strjoin(p->c, p->tmp[n]); */
		printf("new line after getvar loop is %s\n", p->new);
		i += ft_strlen(p->tmp[n]) + 1;
		start = i;
		n++;
	}
	p->new = ft_strjoin(p->new, ft_substr(new_line, i, ft_strlen(new_line) - i));
	printf("new line after everything is %s\n", p->new);
	return (p->new);
}

static int is_there_dollar(char *line, char c)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
			i++;
		}
		else if (line[i] == c && line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != '\"')
			return (1);
		else
			i++;
	}
	return (0);
}

static char  *expand_tilde(t_shell *shell, char *new_line, char **envp, t_var *p)
{	
	int i;
	int j;
	int c;
	char *location;
	char *tmp;

	if (ft_strchr(shell->readline, '~') == NULL)
		return (shell->readline);
	else
	{	
		new_line = ft_strdup("");
		i = 0;
		j = 0;
		c = 0;
		while (shell->readline [i])
		{	
			if (shell->readline[i] == '~' && (shell->readline[i - 1] == ' ' && (shell->readline[i + 1] == ' ' || shell->readline[i +1] == '\0')
				 || (i == 0 && (shell->readline[i + 1] == '\0' || shell->readline[i + 1] == ' '))))
			{	
				/* printf("new line len es %d, i es %d, c es %d\n", j, i, c); */
				new_line = ft_strjoin(ft_substr(new_line, 0, j), ft_substr(shell->readline, i - c, c));
//				printf("line es:%s-\n", new_line);
				j = ft_strlen(new_line);
				c = 0;
				if (search_var_line("HOME", envp) != NULL)
					new_line = ft_strjoin(ft_substr(new_line, 0, j), search_var_line("HOME", envp));
				else
				{
					tmp = ft_strjoin("/home/", shell->user);
					new_line = (ft_substr(new_line, 0, j), tmp);
				}
			}
			else
				c++;
			i++;
			j = ft_strlen(new_line);
		}
		if (c > 1)
			new_line = ft_strjoin(new_line, ft_substr(shell->readline, i - c, i));
		return (new_line);
	}
}

char	*expand_meta(t_shell *shell, char *line, char **envp)
{
	t_var	p;
//	int		n;
	char *new_line;

	new_line = expand_tilde(shell, new_line, envp, &p);
	//printf("line after expand tilde es %s\n", new_line);
	if (is_there_dollar(line, '$') == 0)
		return (new_line);
	p.tmp = ft_split_meta(new_line, '$');
	//printf("split meta array is: \n");
	ft_printarr(p.tmp);
	p.new = NULL;
	/* n = 1;
	if (line[0] == '$')
	{
		p.new = NULL;
		n = 0;
	} */ 
	new_line = get_var(shell, &p, new_line, 0);
	//printf("line after expand meta es %s\n", new_line);
	return (new_line);
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

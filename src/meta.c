/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:38:46 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/31 19:38:00 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	get_var(t_shell *shell, t_var *p, char **envp, int n)
{
	int		j;

	while (p->tmp[n])
	{
		j = 0;
		if (p->tmp[n][j] == '?' && (p->tmp[n][j + 1] == '\0' || p->tmp[n][j + 1] == ' ')) //exit code
		{	
			j++;
			p->exp = ft_itoa(shell->exit);
		}
		else
		{
			while (p->tmp[n][j] &&
				((p->tmp[n][j] >= 'a' && p->tmp[n][j] <= 'z') ||
				(p->tmp[n][j] >= 'A' && p->tmp[n][j] <= 'Z') ||
				(p->tmp[n][j] >= '0' && p->tmp[n][j] <= '9')))
			j++;
			p->var = ft_substr(p->tmp[n], 0, j);
			p->exp = search_var_line(p->var, envp);
		}
			p->c = ft_strjoin(p->new, p->exp);
			p->tmp[n] += j;
			p->new = ft_strjoin(p->c, p->tmp[n]);
		n++;
	}
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
		else if (line[i] == c && line[i + 1] != ' ' && line[i + 1] != '\0')
			return (1);
		else
			i++;
	}
	return (0);
}

char	*expand_meta(t_shell *shell, char *line, char **envp)
{
	t_var	p;
	int		n;

	if (is_there_dollar(line, '$') == 0)
		return (line);
	p.tmp = ft_split_meta(line, '$');

	p.new = p.tmp[0];
	n = 1;
	if (line[0] == '$')
	{
		p.new = NULL;
		n = 0;
	}
	get_var(shell, &p, envp, n);
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

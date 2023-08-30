/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:38:46 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/30 12:06:04 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*meta_str(char const *s, char c, int *n)
{
	int		i;
	char	*new;

	i = 0;
	if (*s == '?' && ++s)
		i++;
	else
		while (*s && ((*s >= 'A' && *s <= 'Z')
			|| (*s >= 'a' && *s <= 'z')
			|| (*s >= '0' && *s <= '9')
			|| (*s >= '_'))
			&& ++i)
			s++;
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
			while (*s && *s != c && ++j)
			{
				if (*s == '\'' && ++s)
				{
					if (*(s - 1) == '$')
						j--;
					while (*s && *s != '\'')
						s++;
				}
				s++;
			}
		else
			++s;
	}
	return (j);
}

int search_dollar(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'' && ++i)
			while (s[i] && s[i] != '\'')
				i++;
		i++;
	}
	return (i);
}

char	**ft_split_meta(char const *s, char c)
{
	int		j;
	int		i;
	char	**res;

//	printf("count meta = %d\n", words_meta(s, c));
	res = (char **) malloc((words_meta(s, c) * (sizeof(char *))) + 8);
	if (!res || !s)
		return (0);
	j = 0;
	while (*s)
	{	
//		printf("*s es %c\n", *s);
		s += search_dollar(s, c);
		if (*s == '\0')
			break;
		++s;
//		printf("*s es %c\n", *s);
//		printf("*s es %s\n", s);
		if (*s != c)
		{
			i = 0;
			res[j++] = meta_str(s, c, &i);
//			printf("substr is %s, i es %d\n", res[j], i);
			s += i;
//			printf("*s es %s\n", s);
		}
		else
			++s;
	}
	res[j++] = NULL;
	return (res);
}

void	make_p(t_shell *shell, t_var *p, char *new_line, int n)
{
	int j;

	j = 0;
	if (p->tmp[n][j] == '?' && ++j) //exit code
		p->exp = ft_itoa(shell->exit);
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
			while (p->tmp[n][j] && ((p->tmp[n][j] >= 'a' && p->tmp[n][j] <= 'z')
				|| (p->tmp[n][j] >= 'A' && p->tmp[n][j] <= 'Z')
				|| (p->tmp[n][j] >= '0' && p->tmp[n][j] <= '9')
				|| (p->tmp[n][j] == '_')))
				j++;
			p->var = ft_substr(p->tmp[n], 0, j);
			p->exp = search_var_line(p->var, shell->envp);
		}
	}
}

static char	*get_var(t_shell *shell, t_var *p, char *new_line, int n)
{
	int		j;
	int 	i;
	int start;
	char	*tmp;

//	printf("ptmp0 es %s y len es %ld\n, new line es %s, y len de new line es %ld\n", p->tmp[n], ft_strlen(p->tmp[n]), new_line, ft_strlen(new_line));
		
	i = 0;
	start = 0;
	while (new_line[i] && p->tmp[n])
	{	
//		printf("start is %c and i es %d\n", new_line[start], i);
//		printf("newline before = <<%s>>\n", new_line + i);
		while (new_line[i] != '$')
		{
			if (new_line[i] == '\'' && ++i)
				while (new_line[i] && new_line[i] != '\'')
					i++;
			i++;
		}
//		printf("newline after = <<%s>>\n", new_line + i);
		make_p(shell, p, new_line, n);
		//free(p->var);
//		printf("newline substr is %s\n", ft_substr(new_line, start, i));
		tmp = ft_substr(new_line, start, i - start);
		p->c = ft_strjoin(tmp, p->exp);
		free(tmp);
		tmp = p->new;
		p->new = ft_strjoin(tmp, p->c);
		free(tmp);
		i += ft_strlen(p->tmp[n]) + 1;
		start = i;
		n++;
	}
	tmp = ft_substr(new_line, i, ft_strlen(new_line) - i);
	p->new = ft_strjoin(p->new, tmp);
	free(tmp);
	free(new_line);
//	printf("new line after everything is %s\n", p->new);
	return (p->new);
}

static int is_there_dollar(char *line, char c)
{
	int i;

	i = 0;
	while (line[i])
	{	
		if (line[i] == '\"' && ++i)
		{
			if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"')
				return (1);
			while (line[i] != '\"' && ++i)
				if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"')
					return (1);
		}
		else if (line[i] == '\'' && ++i)
			while (line[i] != '\'')
				i++;
		else if (line[i] == c && line[i + 1] != ' '
			&& line[i + 1] != '\0' && line[i + 1] != '\"')
			return (1);
		i++;
	}
	return (0);
}
static int check_for_tilde(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{	
		if (line[i] == '\'' && ++i)
		{	
			while (line[i] != '\'')
				i++;
		}
		else if (line[i] == '\"' && ++i)
			while (line[i] != '\"')
				i++;
		else if (line[i] == '~' && ((i == 0 && (line[i + 1] == '\0'
			|| line[i + 1] == ' ')) || (line[i - 1] == ' '
			&& (line[i + 1] == ' ' || line[i + 1] == '\0'))))
			return (1);
		i++;
	}
	return (0);
}

static char  *expand_tilde(t_shell *shell, char *new_line, char **envp, t_var *p)
{	
	int i;
	int j;
	int c;
	char *tmp1;
	char *tmp2;

	if (check_for_tilde(shell->readline) == 0)
	{	
		//printf("sale de check tilde\n");
		new_line = ft_strdup(shell->readline);
		return (new_line);
	}
	else
	{	
		new_line = ft_strdup("");
		i = 0;
		j = 0;
		c = 0;
		while (shell->readline [i])
		{	
			if (shell->readline[i] == '~' && (i == 0
				&& (shell->readline[i + 1] == '\0'
				|| shell->readline[i + 1] == ' '))
				|| (shell->readline[i - 1] == ' '
				&& (shell->readline[i + 1] == ' '
				|| shell->readline[i +1] == '\0')))
			{	
				//printf("entra en tilde correcta\n");
				tmp1 = ft_substr(new_line, 0, j);
				tmp2 = ft_substr(shell->readline, i - c, c);
				//free(new_line);
				new_line = ft_strjoin(tmp1, tmp2);
//				printf("line es:%s-\n", new_line);
				//free(tmp1);
				//free(tmp2);
				j = ft_strlen(new_line);
				c = 0;
				if (search_var_line("HOME", envp) != NULL)
				{
					tmp1 = ft_substr(new_line, 0, j);
					new_line = ft_strjoin(tmp1, search_var_line("HOME", envp));
					//free(tmp1);
				}
				else
				{
					tmp1 = ft_strjoin("/home/", shell->user);
					tmp2 = ft_substr(new_line, 0, j);
					new_line = (tmp2, tmp1);
					//free(tmp1);
					//free(tmp2);
				}
			}
			else
				c++;
			i++;
			j = ft_strlen(new_line);
		}
		if (c > 1)
		{
			tmp1 = ft_substr(shell->readline, i - c, i);
			new_line = ft_strjoin(new_line, tmp1);
			free(tmp1);
		}	
		return (new_line);
	}
}

char	*expand_meta(t_shell *shell, char **envp)
{
	t_var	p;
//	int		n;
	char *new_line;

	//printf("line before expand tilde es %s\n", shell->readline);
	new_line = expand_tilde(shell, new_line, envp, &p);
//	printf("aqui\n");
	free(shell->readline);
//	printf("line after expand tilde es %s\n", new_line);
	if (is_there_dollar(new_line, '$') == 0)
	{	
		//printf("no hay expansion de variable\n");
		return (new_line);
	}
	p.tmp = ft_split_meta(new_line, '$');
	//printf("aqui\n");
//	printf("\nsplit meta array is: \n");
//	ft_printarr(p.tmp);
	p.new = NULL;
	/* n = 1;
	if (line[0] == '$')
	{
		p.new = NULL;
		n = 0;
	} */ 
	new_line = get_var(shell, &p, new_line, 0);
	free_m(p.tmp);
	//free(shell->readline);
//	printf("line after expand meta es <<<%s>>>\n", new_line);
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

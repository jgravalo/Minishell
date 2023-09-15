/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_marks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:29:05 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/15 12:21:05 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int count_backslash(char *s)
{
	int c;

	c = 0;
	while (*s)
	{
		if (*s == '\\' && *(s + 1) == '\\')
		{
			c++;
			s += 2;
		}
		else
			s++;
	}
	//printf("backslash are %d\n", c);
	return (c);
}

char *remove_backslash(char *s)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = malloc(sizeof (char) * ft_strlen(s) - count_backslash(s) + 1);
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == '\\')
		{
			i++;
			new[j++] = s[i++];
		}
		else if (s[i] == '\\' && s[i + 1] == '\"')
		{
			i++;
			new[j++] = s[i++];
		}
		else
			new[j++] = s[i++];
	}
	return (new);
}

static char	*free_quotes(char *s, int n_quotes)
{
	char	*new;
	char	quote;
	int i;
	int j;

	quote = 0;
	i = 0;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(s) - (n_quotes * 2 + 1));
	while (s[i])
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '\"'))
		{
			quote = s[i];
			i++;
		}
		else if (quote == s[i])
		{
			i++;
			quote = 0;
		}
		else
		{
			new[j] = s[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}

int	words(const char *s, char c)
{
	int	j;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
			{
				s++;
			}
			j++;
		}
		else
			++s;
	}
	return (j);
}
/*
int	words_double(const char *s, char c)
{
	int	j;

	j = 0;
	while (*s)
	{
		if (*s != c && *(s + 1) != c)
		{
			while (*s && *s != c && *(s + 1) != c)
			{
				s++;
			}
			j++;
		}
		else
			++s;
	}
	return (j);
}
*/

char	*c_str(char const *s, char c, int *n)
{
	int		i;
	char	*new;
	int 	n_quotes;

	i = 0;
	n_quotes = 0;
	while (*s == ' ')
		s++;
	while (*s && *s != c && *s != '\'')
	{	
		//printf("s esta en %s\n", s);
		if (*s == '\'' && *(s - 1) != '\\' && ++s && ++i)
		{	
			n_quotes++;
			while (*s && *s != '\'' && ++i)
                s++;
			s++;
			i++;
		}        
		else if (*s == '\"' && *(s - 1) != '\\' && ++s && ++i)
		{	
			//printf("entra en quote, s esta en %s\n", s);
			n_quotes++;
			while (*s && *s != '\"' && ++i)
				s++;
			s++;
			i++;
		}
		else
		{
			s++;
			i++;
		}
	}
	new = ft_substr(s - i, 0, i);
	if (n_quotes > 0)
		new = free_quotes(new, n_quotes);
	*n = i;
	return (new);
}

/* char	*mark_str(char const *s, char c, int *n)
{
	char	*new;
	int		i;

	i = 0;
	while (*s && !(*s == c && *(s - 1) != '\\') && ++i)
		s++;
	new = ft_substr(s - i, 0, i);
	if (c == '\'')
		new = protect_quotes(new);
	i++;
	*n = i;
	return (new);
} */
/* 
char	**ft_split_loop(char **res, char const *s, char c)
{
	int		j;
	int		i;
	char 	*new;


	new = ft_strdup("");
	j = 0;
	while (*s)
	{	
		res[j] = ft_strdup("");
		while(*s == ' ')
			s++;
		while (*s != c && *s != '\0')
		{	
			i = 0;
			if (*s == '\"' && *(s - 1) != '\\' && ++s)
				new = mark_str(s, '\"', &i);
			else if (*s == '\'' && *(s - 1) != '\\' && ++s)
				new = mark_str(s, '\'', &i);
			else
				new = c_str(s, c, &i);
			s += i;
			res[j] = ft_strjoin(res[j], new);
		//	printf("res es %s\n", res[j]);
		}
		//printf("sale de loop\n");
		j++;
		if (*s != '\0')
			s++;
	}
	res[j] = NULL;
	//ft_printarr(res);
	return (res); */
/* }

char	**ft_split_marks(char const *s, char c)
{
	char	**res;
	char	*freed;

	if (ft_strlen(s) == 0)
		return (NULL);
	//freed = free_quotes(s);
	//printf("s en split marks es %s\n", s);
	res = (char **) malloc((words(s, c) * (sizeof (char *) + 8)));
	if (!res || !s)
		return (0);
	res = ft_split_loop(res, s, c);
	//ft_printarr(res);
	return (res);
}
 */
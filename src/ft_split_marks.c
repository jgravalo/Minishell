/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_marks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:29:05 by jgravalo          #+#    #+#             */
/*   Updated: 2023/07/31 16:19:08 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*mark_str(char const *s, char c, int *n)
{
	char	*new;
	int		i;

	i = 0;
	while (*s && !(*s == c && *(s - 1) != '\\') && ++i)
		s++;
	new = ft_substr(s - i, 0, i);
	*n = i + 1;
	return (new);
}

char	*free_quotes(char *s)
{
	char	*new;
	
	new = malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i])
	{
		if ()
		new[j] = s[i];
		j++;
		i++;
	}
	return (new);
}

char	*c_str(char const *s, char c, int *n)
{
	int		i;
	char	*new;

	i = 0;
	while (*s && *s != c && ++i)
	{
		//parse_quotes
		/*
		 if (*line == '\'' && ++line && ++i)
                    while (*line && *line != '\'' && ++i)
                        line++;
		 */
		s++;
	}
	new = ft_substr(s - i, 0, i);
	//new = free_quotes(new);
	*n = i;
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
char	**ft_split_loop(char **res, char const *s, char c)
{
	int		j;
	int		i;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			i = 0;
			if (*s == '\"' && *(s - 1) != '\\' && ++s)
				res[j++] = mark_str(s, '\"', &i);
			else if (*s == '\'' && *(s - 1) != '\\' && ++s)
				res[j++] = mark_str(s, '\'', &i);
			else
				res[j++] = c_str(s, c, &i);
			s += i;
		}
		else
			++s;
	}
	res[j++] = NULL;
	return (res);
}

char	**ft_split_marks(char const *s, char c)
{
	char	**res;

	res = (char **) malloc((words(s, c) * (sizeof(char *))) + 8);
	if (!res || !s)
		return (0);
	res = ft_split_loop(res, s, c);
	return (res);
}

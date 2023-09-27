/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:57:04 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/09 11:10:09 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count_words(char const *s, char c)
{
	int	word_count;
	int	word;

	word = 1;
	word_count = 0;
	while (*s)
	{
		if (*s != c && word == 1)
		{
			word_count++;
			word = 0;
		}
		else if (*s == c && word == 0)
			word = 1;
		s++;
	}
	return (word_count);
}

static void	ft_strlcpy(char *dst, const char *src, int *cpy, char c)
{
	unsigned int	i;

	i = 0;
	while (src[*cpy] == c)
		(*cpy)++;
	while (src[*cpy] != '\0' && src[*cpy] != c)
	{
		dst[i] = src[*cpy];
		++i;
		(*cpy)++;
	}
	dst[i] = '\0';
}

static size_t	ft_strlen_charset(const char *s, char c, int *pos)
{
	size_t	count;

	count = 0;
	while (s[*pos] == c)
		(*pos)++;
	while (s[*pos] != '\0' && s[*pos] != c)
	{
		count++;
		(*pos)++;
	}
	return (count);
}

static void	ft_free_strs(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	free (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		pos;
	int		cpy;
	int		n;
	size_t	len;

	n = 0;
	pos = 0;
	cpy = 0;
	strs = (char **)malloc(sizeof (char *) * (ft_count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	while (n < ft_count_words(s, c))
	{
		len = ft_strlen_charset(s, c, &pos);
		strs[n] = (char *)malloc(sizeof (char) * (len + 1));
		if (!strs[n])
		{
			ft_free_strs(strs, n);
			return (NULL);
		}
		ft_strlcpy(strs[n++], s, &cpy, c);
	}
	strs[n] = NULL;
	return (strs);
}
/*
#include <stdio.h>

int main(void)
{
    const char *str = ",,,,Hola,que,tal,,,,si,no,,,,quizas";
    char c = ',';
    char **strs;
    int i = 0;

    strs = ft_split(str, c);
   
    while (strs[i] != NULL)
    {
        printf("%s\n", strs[i]);
        i++;
    }
    i = 0;
    while (strs[i] != NULL)
    {
        free(strs[i]);
        i++;
    }
    free (strs);
}
*/

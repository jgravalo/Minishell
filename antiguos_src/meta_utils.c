#include "../inc/minishell.h"

int is_there_dollar(char *line, char c)
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
				if (line[i] == '$' && line[i + 1] != ' ' && is_alpha_num(line[i + 1]) && line[i + 1] != '\"')
					return (1);
		}
		else if (line[i] == '\'' && ++i)
			while (line[i] != '\'')
				i++;
		else if (line[i] == c && line[i + 1] != ' ' && is_alpha_num(line[i + 1])
			&& line[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}
int check_for_tilde(char *line)
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
			|| line[i + 1] == ' ' || line[i + 1] == '/')) || (line[i - 1] == ' '
			&& (line[i + 1] == ' ' || line[i + 1] == '\0' || line[i + 1] == '/'))))
			return (1);
		i++;
	}
	return (0);
}

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
			|| (*s == '_'))
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